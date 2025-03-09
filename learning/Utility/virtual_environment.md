# 가상환경 설정 방법
## 1. VMware Workstation Pro 설치
 - VMware-player-17.5.2-23775571.zip 다운로드 후 압축 해제  
 - VMware 17.5.2 [다운로드](https://softwareupdate.vmware.com/cds/vmw-desktop/player/17.5.2/23775571/windows/core/)  
  
## 2. 가상환경 os(운영체제)로 리눅스를 설치하여 실습
 - 범용 리눅스인 우분투를 사용  
 - ubuntu 22.04 LTS Desktop image download 다운로드  
 - Ubuntu 22.04 [다운로드](https://releases.ubuntu.com/jammy)  

## 3. VMware Player에서 새로운 가상 환경 생성
1) VMware Player을 실행하여 다운로드한 ubuntu 22.04 image 지정  
2) 프로젝트 생성하여 프로젝트명 작성 및 아이디 비번 만들기  
 - 비번은 자주 사용하니, 중요 프로젝트가 아니라면 간단히 만들기  
 - 세부설정: 하드 50\~100GB / 가상 램은 4~8GB / Processors core 6  `코어는 높으면 경고 문구를 띄워주니 안 뜰 때까지 낮추기`  
3) 디폴트값 따라가며 키보드는 나중에 변경하니 아무거나, 시간설정은 서울로 하면 됨  
  
## 4. 표기 언어 및 입력기 언어 한국어 설정
1) 설정에서 지역 및 언어 설정에서 한국을 고른다.  
-> 재부팅 시 ui가 한글로 바뀜  
-> 설정에서 한글로 바꿀 때 파일명에 대해서도 한글로 바꾸는 것은 적용하지 않기  
-> 만약 폴더명도 한글로 바꾸냐고 물어볼 시, “““NO””” 파일명이 한글로 바뀔 시 추후 패스 선언 때 오류 발생 가능.  
3) 입력기에서 한국어를 누르면 (hangle)이 있음  
-> 톱니바퀴 달린 거  
-> 그거 기본 설정에서 한/영 키가 안 먹히므로 대신할 키로 추가해야 한/영 키보드를 이용할 수 있음  
-> 변경 후, 우상단에 입력기를 눌러 한국어(hangle)로 설정 되었는지 확인해주기  
  
## 5. VScode 설치
1) Ubuntu에 맞는 압축 확장자(.deb) 설치 파일을 [다운로드](https://code.visualstudio.com/Download)  
2) 설치된 위치의 터미너에서 ```sudo dpkg -i [패키지이름.deb]```
  
## 6. Git 연동  
1) 터미널에서 git관련 기능 설치  ```$sudo apt-get install git```  
2) Git초기화 및 로컬 저장소 생성 (처음 설정시 적용)  ```$git init```  
3) Git 링크와의 연결  ```$git remote add origin [Git링크]```  
4) .git이란 로컬 저장가 생겼는지 확인  ```$ls -al```
5) GitHub에서 최신 변경사항 가져오기  ```$git fetch origin```
6) 
7) 새로운 브랜치(main)를 만들고, 원격 브랜치(origin/main)를 따라가도록 설정  ```$git checkout -b main origin/main```
6-1) 원격 브랜치 
8) GitHub에서 변경점 가져오기  ```$git pull```
9) 

