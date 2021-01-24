B: 指定Birthday, 例如:B0229 指定2月29日
Y: 指定Year，  例如: Y19761999 指定年份1976-1999  左右包含, [1976,1999]
                       Y19991999  指定1999年
  M: 指定Month，例如:M02 指定2月
  D: 指定Day, 例如:D29, 指定29日

B0320 等价于 M03D20

[注意]: B, Y, M, D 可选，顺序随意；
          当指定B时， 则M,D 指定的月份，日期无效；若 时间冲突，以B指定的时间为准





1.普通查询：输入18位，缺省用*代替

![image](https://github.com/zhang-wqin/train_ticket_IDCardNumber_fill/tree/main/README.assets/image-20210124113508762.png)

![image-20210124113531201](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210124113531201.png)



2.查询指定生日为2月29日

![image-20210124113927500](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210124113927500.png)



3.查询指定 2000-2021年 3月

![image-20210124113156360](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210124113156360.png)

![image-20210124113637189](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210124113637189.png)





4.指定2000-2999 生日为3月31的查询

![image-20210124113402189](C:\Users\Administrator\AppData\Roaming\Typora\typora-user-images\image-20210124113402189.png)

（身份证是20**， 所以2999太大了）
