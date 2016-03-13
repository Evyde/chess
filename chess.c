/*
*头文件区
************************************
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
************************************
*/

/*
*宏定义区
************************************
*/
#define width 21
#define height 21
/*
************************************
*/

/*
*全局变量区
*************************************
*/
int userInput = 1;

char* cls = "clear";//Windows系统请将clear更改为cls

char* chessPanel[width][height];

char* white = "○";
char* black = "●";

char menuOfDebug[][512] = {"更改随机数方式","进行游戏","退出菜单"};
int numOfDebugMenu = 3;
int methodOfDebugMenu = 0;
char menuOfStart[][512] = {"开始游戏","设定","帮助","关于","退出游戏"};
int numOfStartMenu = 5;
int methodOfStartMenu = 0;
char menuOfGameHelp[][512] = {"这个帮助可以让你了解游戏规则及操作方法。","在游戏中，你需要输入形如(x,y)这样的坐标来确定下棋的位置","之后电脑会下棋，此时系统提示电脑下棋坐标","之后继续输入坐标直到胜利即可","胜利条件：五个棋在同一条直线上，且不被对方棋子阻挡","胜利后将会弹出菜单。","必须输入数字，否则后果未知，最轻导致程序无限循环！","0.返回主菜单"};
int numOfGameHelpMenu = 9;
int methodOfGameHelpMenu = 2;
char menuOfAbout[][512] = {"作者：韩枫","邮箱：life.app.hanfeng@hotmail.com","制作时间：2016年03月","版本：V1.0","0.返回主菜单"};
int numOfAboutMenu = 5;
int methodOfAboutMenu = 2;
char menuOfEnding[][512] = {"返回主菜单","结束游戏"};
int numOfEndingMenu = 2;
int methodOfEndingMenu = 0;
/*
*************************************
*/

/*
*函数区
*************************************
*/

/*
*函数名	:	creatPanel
*参数	:	无
*作用	:	创建一个棋盘数组
*/
int creatPanel(void) {
	int i = 0,j = 0;
	for(i = 0;i < height;i++) {
		chessPanel[0][i] = "  ";
	}
	for(i = 0;i < width;i++) {
		chessPanel[i][0] = "  ";
	}
	//四周留空白，以便棋子完整显示，且坐标无需进行运算
	for(i = 1;i < height;i++) {
		for(j = 1;j < width;j++) {
			chessPanel[i][j] = "+ ";
		}
	}
	return 0;
}

/*
*函数名	:	printPanel
*参数	:	无
*作用	:	输出棋盘
*/
int printPanel(void) {
	int i = 0,j = 0;
	for(i = 0;i < height;i++) {
          for(j = 0;j < width;j++) {
              printf("%s",chessPanel[j][i]);
          }
          printf("\n");
      }
	return 0;
}


/*
*函数名	:	creatMenu
*参数	:	menu	:	菜单文字
			numOfChar	:	列表个数
			method	:	输出方式	:	0	:	带序号，默认分隔符，换行输出
										1	:	带序号，自定义分隔符，换行输出
										2	:	不带序号，无分隔符，换行输出
*作用	:	创建菜单并且输出
*/	
int creatMenu(char menu[][512],int numOfChar,int method,char devider) {
	int i = 0;
	for(i = 0;i < numOfChar;i++) {
		switch(method) {
			case 0:{printf("%d.%s\n",i+1,menu[i]);break;}
			case 1:{printf("%d%c%s\n",i+1,devider,menu[i]);break;}
			case 2:{printf("%s\n",menu[i]);break;}
			default :{printf("METHOD IS ERROR!");return 0;}
		}
	}
	return 0;
}

/*
*函数名	:	debug
*参数	:	无
*作用	:	调试程序
*/
int debug(void) {
	printf("开始调试\n");
	creatMenu(menuOfDebug,numOfDebugMenu,methodOfDebugMenu,'.');
	return 0;
}

/*
*函数名	:	startGame
*参数	:	无
*作用	:	开始游戏，进行初始化，并应用程序逻辑
*/
int startGame(void) {
	int x=9,y=9;
	char i = 'n';
	creatPanel();
	system(cls);
	while(1) {
		system(cls);
		printPanel();
		printf("棋盘大小：%d X %d\n",width,height);
		printf("退出游戏请输入棋盘之外坐标即可\n");
		printf("请输入坐标(格式：x,y)：\n");
		scanf("%d,%d",&x,&y);
		if(x > width || y > height) {
			printf("检测到数组越界，是否退出游戏？[y/n]:");
			scanf("%c",&i);
			if(i == 'y' || i == 'Y') return 0;
			else continue;
		}else chessPanel[x][y] = black;
		
	}
	return 0;
}

/*
*函数名	:	setting
*参数	:	无
*作用	:	设置
*/
int setting(void) {

	return 0;
}

/*
*函数名	:	help
*参数	:	无
*作用	:	显示帮助信息
*/
int help() {
	system(cls);
	creatMenu(menuOfGameHelp,numOfGameHelpMenu,methodOfGameHelpMenu,'.');
	scanf("%d",&userInput);
	if(userInput == 0) return 0;
	else help();
	return 0;
}

/*
*函数名	:	about
*参数	:	无
*作用	:	显示关于信息
*/
int about() {
	system(cls);
	creatMenu(menuOfAbout,numOfAboutMenu,methodOfAboutMenu,'.');
	scanf("%d",&userInput);
	if(userInput == 0) return 0;
	else about();
	return 0;
}

/*
*函数名	:	main
*参数	:	argc	:	命令行参数列表
			argv	:	命令行参数
*作用	:	程序入口
*/
int main(int argc,char *argv[]) {
	if (strstr(argv[argc-1] , "Debug")) {
		printf("调试模式！\n");
		if(!debug()) {
			printf("调试完毕！程序退出！\n");
			return 0;
		}else printf("调试失败！程序退出！\n");
		return 0;
	}else printf("游戏模式！\n");
	while(1) {
	system(cls);
	creatMenu(menuOfStart,numOfStartMenu,methodOfStartMenu,'.');
	scanf("%d",&userInput);
	switch(userInput) {
		case 1:{startGame();break;}
		case 2:{setting();break;}
		case 3:{help();break;}
		case 4:{about();break;}
		case 5:{return 0;break;}
		default :continue;
	}
}
		
}
