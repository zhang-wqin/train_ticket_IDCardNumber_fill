/*
Date: 2021.1.23
Author: zhangweiqin
Version: 3.0

  v3.0 可通过普通输入查询,也可以指定生日，指定年份范围,指定月份，日期

  B: 指定Birthday, 例如:B0229 指定2月29日
  Y: 指定Year，  例如: Y19761999 指定年份1976-1999  左右包含, [1976,1999]
                       Y19991999  指定1999年
  M: 指定Month，例如:M02 指定2月
  D: 指定Day, 例如:D29, 指定29日

  [注意]: B, Y, M, D 可选，顺序随意；
          当指定B时， 则M,D 指定的月份，日期无效， 以B指定的时间为准


  样例：
  123456******1234//输入18位普通查询
  12345619******1234B0320//指定生日为3月20日查询
  12345620******1234B03Y20032032//指定2003-2032年3月份出生的查询

*/

#include<stdio.h>
#include<string.h>


const int bit_weight[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
const char validate[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};//mod 11
int months[13] = {0, 31, 28, 31, 30, 31,30, 31,31,30,31, 30, 31};
//                    1   2   3   4   5  6   7  8  9  10  11  12


char id_input[64];
char copy_id_input[32];



int cnt; //输入样例数计数器
int year, month, day;   //记录身份证中的 年、月、日
int upper_year, lower_year; //记录年份的上限与下限，例如1900，1999

int unknow_cnt;
int ans_cnt; //统计匹配到的个数
int Year_marker, Birthday_marker, Month_marker, Day_marker; // B, Y ，M, D 符号标记
int specified_up_year,specified_low_year, specified_month, specified_day; //用于记录指定的时间


int is_leap_year(int year){
	/*  4年一闰，100年不闰，400年再闰 */
	if(year%400 == 0) return 1;
	else if(year%100 == 0) return 0;
	else if(year%4 == 0 ) return 1;
	else return 0;
}

void print_plus_token_line(int n){
    for(int i=0; i<n; ++i)
        putchar('+');
    putchar('\n');
}

int verify_all_fill(){
    int sum =0;
    for(int i=0; i<17; ++i)
        sum += (copy_id_input[i]-'0') * bit_weight[i];
    sum %= 11;
    return copy_id_input[17] == validate[sum]? 1: 0;
}


int pre_process(){
    /* 对输入的身份证号码进行初步的统计处理 */
    year = month = day = 0;
    upper_year = lower_year = 0;
    unknow_cnt = 0;

    Year_marker = Birthday_marker = 0;
    Month_marker = Day_marker = 0;

    specified_month = specified_day = 0;
    specified_up_year = specified_low_year = 0;
    int year_unknow_cnt = 0;

    // 记录B， Y, M, D 键的位置
    for(int i=0, len = strlen(id_input); i<len; ++i)
        if(id_input[i] == '*')
            unknow_cnt ++;
        else if(id_input[i] == 'Y')
            Year_marker = i;
        else if(id_input[i] == 'B')
            Birthday_marker = i;
        else if(id_input[i] == 'M')
            Month_marker = i;
        else if(id_input[i] == 'D')
            Day_marker = i;

    //统计年份的*符号数
    for(int i=6; i<10; ++i)
        if(id_input[i] == '*')
            year_unknow_cnt ++;

    // 处理年份
    if(year_unknow_cnt == 0){//4位年份 都已知,直接处理
        for(int i=6; i<10; ++i){
            year = year*10 + (id_input[i] - '0');
        }
        //goto __process_month;
    }else if(id_input[6] == '*'){ //年份第一位 未知

    }else if(id_input[6] == '1'){// 必定是1900-1999年之间
        //id_input[7] == '9';
        lower_year = 1900, upper_year = 1999;
    }else if(id_input[6] == '2'){// 必定是2000-2025年之间
        //id_input[7] == '0';
        lower_year = 2000, upper_year = 2025;
    }

    /*
    //处理月份
    __process_month:

    //处理日期
    */

    //分离出 指定年份范围时
    if(Year_marker){
        int y = Year_marker;

        int tmp = 0;
        for(int i = y+1; i <= y+4; ++i){
            tmp = tmp*10 + (id_input[i]-'0');
        }
        specified_low_year = tmp, tmp = 0;


        for(int i = y+5; i <= y+8; ++i){
            tmp = tmp*10 + (id_input[i]-'0');
        }
        specified_up_year = tmp;
    }

    //分离出 指定月份时
    if(Month_marker){
        int m = Month_marker;
        specified_month = (id_input[m+1]-'0')*10 + id_input[m+2]-'0';
    }

    //分离出 指定日期时
    if(Day_marker){
        int d = Day_marker;
        specified_day = (id_input[d+1]-'0')*10 + id_input[d+2]-'0';
    }


    //分离出 指定生日时 的月份和日期
    if(Birthday_marker){
        int b = Birthday_marker;
        specified_month = (id_input[b+1]-'0')*10 + id_input[b+2]-'0';
        specified_day = (id_input[b+3]-'0')*10 + id_input[b+4]-'0';
    }

    return 1;
}


int fill_unknow(){
    ans_cnt = 0;
    memcpy(copy_id_input, id_input, 18);
    for(int t,i=0; i<999999; ++i){
        t = i;

        //判断日期是否符合范围
        if((day = t%100) > 31) continue; // 日期超过31，排除
        if( specified_day && specified_day != day ) continue;
        // specified_day为0， 表示未指定生日, 下同


        //判断月份是否符合范围
        if((month = (t/100%100)) > 12) continue; //月份超过12， 排除
        if( specified_month && specified_month != month ) continue;


        // 注意bugger, lower_year = 0, year 可能冲突
        //判断年份是否符合范围
        year = lower_year + t/10000;
        if(Year_marker &&
           (year < specified_low_year || year > specified_up_year)){
            continue;
        }


        if(is_leap_year(year)){
            months[2] = 29;
        }else{
            months[2] = 28;
        }

        if(day > months[month]) continue; //日期超过该月的最大天数


        //将日期填入数组
        for(int j=13; j>=8; --j){
            copy_id_input[j] = t%10+'0';
            t /= 10;
        }


        //验证是否符合
        if(verify_all_fill()){
            printf("%s\n", copy_id_input);
            ans_cnt ++;
        }
    }

    return 0;
}


int main(){
    printf("输入18位身份证号码，缺省用*代替，每行回车，以EOF结束 (Ctrl+Z)\n\n");

    printf("in_%d:\n",++cnt); //第1组输入
	while(~scanf("%s", id_input)){
        print_plus_token_line(40);

        pre_process();
        fill_unknow();
        printf("共匹配到: %d条\n", ans_cnt);
        print_plus_token_line(40);
        printf("\n\n");

        printf("in_%d:\n",++cnt); //第2~n组输入
	}

	return 0;
}

