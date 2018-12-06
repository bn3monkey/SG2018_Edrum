
install qmake package

	sudo apt-get install gq5-qmake


해당 폴더로 들어 간 후,

	qmake

그러면 Makefile이 생성된다. 이 후,

	make

명령을 치면 컴파일이 되어 실행파일이 생기므로, 그것을 실행한다.



 * 만약 안되는 경우 밑의 명령어를 쳐본 후 qmake 부터 시작한다.

	sudo apt-get install aptitude
	aptitude show qt5-default	

작성자 : 김상섭 2018.12.6
