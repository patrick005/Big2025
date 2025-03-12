```
sudo apt update
sudo apt upgrade
sudo apt install mysql-server
```
```
dpkg -l(엘) | grep mysql
mysql --version
```
```
sudo mysql_secure_installation
```
key->n  
ann->보안 y  
disallow root -> 권한막기 n  
database-> y  
privilege -> y  
```
sudo systemctl status mysql
```
-> 첫페이지 active인지 확인  
```
sudo systemctl enable mysql
```
->부팅시에도 다시 재시작  
```
sudo mysql -u root -p
```
-> mysql 접속명령어  
```
use mysql;
select * from user;
select host, user from user;
```
-> 해당 테이블 확인  
```

alter user root@localhost identified with 'mysql_native_password' by '0000';
flush privileges;
```
-->안되면 https://developnote.tistory.com/34 참조  

```
//어라 이게어디갓지
```
-> 외부 접근 가능 유저 추가  
```
select host, user from user;
```
-> 추가 확인  
```
exit
```
-> mysql 탈출  

---
```
mysql -u root -p
```
->위 설정이 끝났으면 sudo없이도 접근 가능해야함  
-> 비번설정따로 안했으면 '0000'  

====================
vscode 확장프로그램 jun han의 mysql 설치해주기  
