/*
Date: 2021.1.23
Author: zhangweiqin
Version: 3.0

  v3.0 ��ͨ����ͨ�����ѯ,Ҳ����ָ�����գ�ָ����ݷ�Χ,ָ���·ݣ�����

  B: ָ��Birthday, ����:B0229 ָ��2��29��
  Y: ָ��Year��  ����: Y19761999 ָ�����1976-1999  ���Ұ���, [1976,1999]
                       Y19991999  ָ��1999��
  M: ָ��Month������:M02 ָ��2��
  D: ָ��Day, ����:D29, ָ��29��

  [ע��]: B, Y, M, D ��ѡ��˳�����⣻
          ��ָ��Bʱ�� ��M,D ָ�����·ݣ�������Ч�� ��Bָ����ʱ��Ϊ׼


  ������
  123456******1234//����18λ��ͨ��ѯ
  12345619******1234B0320//ָ������Ϊ3��20�ղ�ѯ
  12345620******1234B03Y20032032//ָ��2003-2032��3�·ݳ����Ĳ�ѯ

*/

#include<stdio.h>
#include<string.h>


const int bit_weight[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
const char validate[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};//mod 11
int months[13] = {0, 31, 28, 31, 30, 31,30, 31,31,30,31, 30, 31};
//                    1   2   3   4   5  6   7  8  9  10  11  12


char id_input[64];
char copy_id_input[32];



int cnt; //����������������
int year, month, day;   //��¼���֤�е� �ꡢ�¡���
int upper_year, lower_year; //��¼��ݵ����������ޣ�����1900��1999

int unknow_cnt;
int ans_cnt; //ͳ��ƥ�䵽�ĸ���
int Year_marker, Birthday_marker, Month_marker, Day_marker; // B, Y ��M, D ���ű��
int specified_up_year,specified_low_year, specified_month, specified_day; //���ڼ�¼ָ����ʱ��


int is_leap_year(int year){
	/*  4��һ��100�겻��400������ */
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
    /* ����������֤������г�����ͳ�ƴ��� */
    year = month = day = 0;
    upper_year = lower_year = 0;
    unknow_cnt = 0;

    Year_marker = Birthday_marker = 0;
    Month_marker = Day_marker = 0;

    specified_month = specified_day = 0;
    specified_up_year = specified_low_year = 0;
    int year_unknow_cnt = 0;

    // ��¼B�� Y, M, D ����λ��
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

    //ͳ����ݵ�*������
    for(int i=6; i<10; ++i)
        if(id_input[i] == '*')
            year_unknow_cnt ++;

    // �������
    if(year_unknow_cnt == 0){//4λ��� ����֪,ֱ�Ӵ���
        for(int i=6; i<10; ++i){
            year = year*10 + (id_input[i] - '0');
        }
        //goto __process_month;
    }else if(id_input[6] == '*'){ //��ݵ�һλ δ֪

    }else if(id_input[6] == '1'){// �ض���1900-1999��֮��
        //id_input[7] == '9';
        lower_year = 1900, upper_year = 1999;
    }else if(id_input[6] == '2'){// �ض���2000-2025��֮��
        //id_input[7] == '0';
        lower_year = 2000, upper_year = 2025;
    }

    /*
    //�����·�
    __process_month:

    //��������
    */

    //����� ָ����ݷ�Χʱ
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

    //����� ָ���·�ʱ
    if(Month_marker){
        int m = Month_marker;
        specified_month = (id_input[m+1]-'0')*10 + id_input[m+2]-'0';
    }

    //����� ָ������ʱ
    if(Day_marker){
        int d = Day_marker;
        specified_day = (id_input[d+1]-'0')*10 + id_input[d+2]-'0';
    }


    //����� ָ������ʱ ���·ݺ�����
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

        //�ж������Ƿ���Ϸ�Χ
        if((day = t%100) > 31) continue; // ���ڳ���31���ų�
        if( specified_day && specified_day != day ) continue;
        // specified_dayΪ0�� ��ʾδָ������, ��ͬ


        //�ж��·��Ƿ���Ϸ�Χ
        if((month = (t/100%100)) > 12) continue; //�·ݳ���12�� �ų�
        if( specified_month && specified_month != month ) continue;


        // ע��bugger, lower_year = 0, year ���ܳ�ͻ
        //�ж�����Ƿ���Ϸ�Χ
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

        if(day > months[month]) continue; //���ڳ������µ��������


        //��������������
        for(int j=13; j>=8; --j){
            copy_id_input[j] = t%10+'0';
            t /= 10;
        }


        //��֤�Ƿ����
        if(verify_all_fill()){
            printf("%s\n", copy_id_input);
            ans_cnt ++;
        }
    }

    return 0;
}


int main(){
    printf("����18λ���֤���룬ȱʡ��*���棬ÿ�лس�����EOF���� (Ctrl+Z)\n\n");

    printf("in_%d:\n",++cnt); //��1������
	while(~scanf("%s", id_input)){
        print_plus_token_line(40);

        pre_process();
        fill_unknow();
        printf("��ƥ�䵽: %d��\n", ans_cnt);
        print_plus_token_line(40);
        printf("\n\n");

        printf("in_%d:\n",++cnt); //��2~n������
	}

	return 0;
}

