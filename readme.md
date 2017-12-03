# 라이브러리

## man 페이지
- 각 번호로 동일한 명령에 대한 범주화를 갖고 있다
- bash(1), system call(2), api(3), others(5)
- man 1 printf : bash printf 에 대한 설명
- man 3 printf : c printf api 에 대한 설명
- man -a {command} 로 관련된 모든 페이지 조회
- man -k {command} 로 관련된 모든 manual 조회

## doxygen

## gdb

## pkg-config
- gcc {source code} `pkg-config glib-2.0 --cflags --libs`
- --list-all 설치된 모든 라이브러리 확인
- --cflags는 include directory 표시
- --libs는 library 지정
- \`\` 작은 따옴표는 명령행 실행 전 내부 명령을 실행하여 결과를 치환한다

## 시스템콜

### 정적링크
- 컴파일타임에 결합
- /lib, /usr/lib, /usr/local/lib/.a
- -static 옵션이 없으면 기본적으로 동적링크로 컴파일

### 동적링크
1. 동적링크
- 프로그램이 로드되면 바로 연결 (printf)
2. 동적로드
- 프로그램 실행 중 자유자재로 로드
- dlopen으로 so(shared object) 파일을 로드하고
- dlsym으로 함수포인터에 동작을 로드해서 사용
- dlclose로 종료

### 심볼스코프
- 라이브러리를 이용할 때 기존 심볼과 api가 유효한지 확인하는 것은 중요하다
- static 이나 scope 기호를 이용해서 심볼의 유효스코프를 제한할 수 있다
- nm -g {library.a} 명령을 통해서 외부에 공개된 심볼을 확인할 수 있다
