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
#define width 22
#define height 22
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
int chessPlot[width-2][height-2];

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
	//四周留空白，以便棋子完整显示
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
              printf("%s\t",chessPanel[j][i]);
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
*函数名	:	exitGame
*参数	:	无
*作用	:	游戏结束后调用，重置变量
*/
int exitGame(void) {

	return 0;
}

/*
*函数名	:	isVictory
*参数	:	numOfChess	:	棋子代码，代表黑棋和白棋
						1	:	黑棋
						2	:	白棋
			x	:	用户下棋X坐标
			y	:	用户下棋Y坐标
*作用	:	判断是否胜利，胜利返回1，否则返回0
*/
int isVictory(int numOfChess,int x,int y) {
	int chess,i = 0,j = 0,totalChess = 1;
	chess = numOfChess;
	//开始判断
	/*
	算法逻辑说明：
		五子棋，即五个棋子连在一起即可，所以需要判断横向、竖向、以及斜线，总共四次
		可以用以下方式：
			例如横向，以当前棋子为中心点，向左统计相同棋子个数，向右统计相同棋子个数，如果和大于等于5，就判定胜利。
		其它方向以此类推。
	*/
	//横向
	for(i = x-1;i > 0;i--) {
		if(chessPlot[i][y] == chess) totalChess++;
		else break;
	}
	for(i = x+1;i < (width - 2);i++) {
		if(chessPlot[i][y] == chess) totalChess++;
		else break;
	}
	if(totalChess >= 5) return 1;
	totalChess = 1;
	//纵向
	for(i = y-1;i > 0;i--) {
		if(chessPlot[x][i] == chess) totalChess++;
		else break;
	}
	for(i = y+1;i < (height-2);i++) {
		if(chessPlot[x][i] == chess) totalChess++;
		else break;
	}
	if(totalChess >= 5) return 1;
	totalChess = 1;
	//左上到右下方向
	//左上
	i = x-1;
	j = y-1;
	for(;i > 0 && j > 0;) {
		if(chessPlot[i][j] == chess) totalChess++;
		else break;
		i--;
		j--;
	}
	//左下
	i = x+1;
	j = y+1;
	for(;i < (width-2) && j < (height-2);) {
		if(chessPlot[i][j] == chess) totalChess++;
		else break;
		i--;
		j--;
	}
	if(totalChess >= 5) return 1;
	totalChess = 1;
	//右上到左下方向
	//右上
	i = x+1;
	j = y-1;
	for(;i < (width-2) && j > 0;) {
		if(chessPlot[i][j] == chess) totalChess++;
		else break;
		i++;
		j--;
	}
	//右下
	i = x-1;
	j = y+1;
	for(;i > 0 && j < (height-2);) {
		if(chessPlot[i][j] == chess) totalChess++;
		else break;
		i--;
		j++;
	}
	if(totalChess >= 5) return 1;
	else return 0;
}

/*
*函数名	:	AIPlot
*参数	:	x	:	用户下的X坐标
			y	:	用户下的Y坐标
*说明	:	电脑下棋，在用户棋子周围3格内下棋
*/
int AIPlot(int x,int y) {
	//srand(time(0));
	
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
*函数名	:	endGame
*参数	:	isVictory	:	表示玩家或者电脑胜利
							0	:	代表玩家胜利
							1	:	代表电脑胜利
*作用	:	结束游戏后调用
*/
int endGame(int isVictory) {
	int a=0;
	system(cls);
	if(isVictory == 0) printf("玩家获胜！\n0.返回主菜单\n1.退出游戏\n");
	else printf("玩家失败！\n0.返回主菜单\n1.退出游戏\n");
	scanf("%d",&a);
	if(a == 0) return 0;
	else exit(0);
}

/*
*函数名	:	isPloted
*参数	:	x	:	下棋的X坐标
			y	:	下棋的Y坐标
*作用	:	判断是否已经下棋，是返回1
*/
int isPloted(int x,int y) {
	if(chessPlot[x][y] != 0) return 1;
	else return 0;
}

/*
*函数名	:	startGame
*参数	:	无
*作用	:	开始游戏，进行初始化，并应用程序逻辑
*/
int startGame(void) {
	int x = 9,y = 9;
	char i = 'n';
	creatPanel();
	system(cls);
	while(1) {
		system(cls);
		printPanel();
		printf("棋盘大小：%d X %d\n",width-2,height-2);
		printf("退出游戏请输入棋盘之外坐标即可\n");
		printf("请输入坐标(格式：x,y)：\n");
		scanf("%d,%d",&x,&y);
		system(cls);
		if(x > (width - 2) || y > (height - 2)) {
			system(cls);
			printf("检测到数组越界，是否返回主菜单？[y/n]:");
			scanf("%c",&i);
			system(cls);
			if(i == 'y' || i == 'Y') {
				exitGame();
				return 0;
			}
			else continue;
		}else if(isPloted(x,y) == 1) continue;
		chessPlot[x][y] = 1;//1代表黑棋
		if(isVictory(1,x,y) == 1) {
			endGame(0);
			return 0;
		}
		//AIPlot(x,y);
		//isVictory(2);
		chessPanel[x+1][y+1] = black;
		
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
	int i,j;
	if (strstr(argv[argc-1] , "Debug")) {
		printf("调试模式！\n");
		if(!debug()) {
			printf("调试完毕！程序退出！\n");
			return 0;
		}else printf("调试失败！程序退出！\n");
		return 0;
	}else printf("游戏模式！\n");
	for(i = 0;i < (width - 2);i++) {
		for(j = 0;j < (height - 2);j++) {
			chessPlot[i][j] = 0;
		}
	}
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
