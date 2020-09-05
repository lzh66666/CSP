#include <bits/stdc++.h>

using namespace std;

void trim(string &s){
	if(!s.empty()){
    	s.erase(0,s.find_first_not_of(" "));
    	s.erase(s.find_last_not_of(" ") + 1);
 	}
}

int main(){

	vector<string> vet;
	string line;
	
	int i = 0;
	int j = 0;
	int ul = 1;
	while(getline(cin,line)){
		ul = 1;
     	if(line.length() > 0){
			while(line.find('_') != string::npos){
				line.replace(line.find('_'),1,"<em>");
				line.replace(line.find('_'),1,"</em>");
			}

			while(line.find('[') != string::npos){
				line.replace(line.find(']'),1,"</a>");
				
				int start = line.find('(');
				line.erase(line.begin()+start);
				int end = line.find(')');
				string ss = line.substr(start,end-start);
				line.erase(start,end-start+1);
				string s = "<a href=\"" + ss + "\">";

				line.replace(line.find('['),1,s);
			}

			if(line[0] == '*' || (vet.size()>1 && vet[vet.size()-1].find("<li>") != string::npos)){
				string s = line.substr(1);
				trim(s);
				if(vet.size()>0 && vet[vet.size()-1].find("<li>") != string::npos){
					if(line[0] != '*'){
						ul = 1;
						vet.push_back("</ul>");
					}else{
						if(j+1 != i){
							vet.push_back("</ul>");
							vet.push_back("<ul>");
						}
						ul = 0;
						vet.push_back("<li>" + s + "</li>");
					}
				}else{
					vet.push_back("<ul>");
					vet.push_back("<li>" + s + "</li>");
					ul = 0;
				}
			}
			if(line[0] == '#'){
				int start = line.find(' ');
				stringstream s;s << start;string num = s.str();
				string str = line.substr(start);
				trim(str);
				str = "<h" + num + ">" + str + "</h" + num + ">";
				vet.push_back(str);
			}else if(line[0] != '*'){
				if(j+1 == i  && vet[vet.size()-1].find("</p>") != string::npos){
					string str = vet[vet.size()-1];
					vet[vet.size()-1] = str.substr(0,str.size()-4);
					vet.push_back(line + "</p>");
				}else{
					vet.push_back("<p>" + line + "</p>");
				}
			}
     		j = i;
		}
		i++;
		if(i == 21){
			break;
		}
	}



	for(int k = 0; k < vet.size(); k++){
		cout << vet[k] << endl;
	}

	if(ul != 1){
		cout << "</ul>";
	}
	return 0;
}

/*=================================================================
输入
# Hello

Hello, world!
输出
<h1>Hello</h1>
<p>Hello, world!</p>

输入
* peare1
# _Heading_
##### Heading

## Sub-heading

Paragrapha are separated
_A_ [link](http://exaup1e.com)
by a blank line.

Text attributes _italic_.
* applea
* orangea
* peare2

* peare3

_A_ [link](http://exaup1e.com)
123

* peare4
输出
<h5>Heading</h5>
<h2>Sub-heading</h2>
<p>Paragrapha are separated
by a blank line.</p>
<p>Text attributes<em>italic</em>.</p>
<p>Bullet list:</p>
<ul>
<li>applea</li>
<li>orangea</li>
<li>peare</li>
</ul>
<p><em>A</em> <a href="http://exaup1e.com">link</a>.</p>
=================================================================*/
/*
问题描述
　　Markdown 是一种很流行的轻量级标记语言（lightweight markup language），广泛用于撰写带格式的文档。
例如以下这段文本就是用 Markdown 的语法写成的：如图031.jpg
这些用 Markdown 写成的文本，尽管本身是纯文本格式，然而读者可以很容易地看出它的文档结构。同时，还有很
多工具可以自动把 Markdown 文本转换成 HTML 甚至 Word、PDF 等格式，取得更好的排版效果。例如上面这段文本
通过转化得到的 HTML 代码如图032.jpg所示：
本题要求由你来编写一个 Markdown 的转换工具，完成 Markdown 文本到 HTML 代码的转换工作。简化起见，本题定
义的 Markdown 语法规则和转换规则描述如下：
　　●区块：区块是文档的顶级结构。本题的 Markdown 语法有 3 种区块格式。在输入中，相邻两个区块之间用一个
或多个空行分隔。输出时删除所有分隔区块的空行。
　　○段落：一般情况下，连续多行输入构成一个段落。段落的转换规则是在段落的第一行行首插入 `<p>`，在最后一
行行末插入 `</p>`。
　　○标题：每个标题区块只有一行，由若干个 `#` 开头，接着一个或多个空格，然后是标题内容，直到行末。`#` 的
个数决定了标题的等级。转换时，`# Heading` 转换为 `<h1>Heading</h1>`，`## Heading` 转换为 `<h2>Heading</h2>`，
以此类推。标题等级最深为 6。
　　○无序列表：无序列表由若干行组成，每行由 `*` 开头，接着一个或多个空格，然后是列表项目的文字，直到行末。
转换时，在最开始插入一行 `<ul>`，最后插入一行 `</ul>`；对于每行，`* Item` 转换为 `<li>Item</li>`。本题中的
无序列表只有一层，不会出现缩进的情况。
　　●行内：对于区块中的内容，有以下两种行内结构。
　　○强调：`_Text_` 转换为 `<em>Text</em>`。强调不会出现嵌套，每行中 `_` 的个数一定是偶数，且不会连续相邻。
注意 `_Text_` 的前后不一定是空格字符。
　　○超级链接：`[Text](Link)` 转换为 `<a href="Link">Text</a>`。超级链接和强调可以相互嵌套，但每种格式不会
超过一层。
输入格式
　　输入由若干行组成，表示一个用本题规定的 Markdown 语法撰写的文档。
输出格式
　　输出由若干行组成，表示输入的 Markdown 文档转换成产生的 HTML 代码。
样例输入
# Hello

Hello, world!
样例输出
<h1>Hello</h1>
<p>Hello, world!</p>
评测用例规模与约定
　　本题的测试点满足以下条件：
　　●本题每个测试点的输入数据所包含的行数都不超过100，每行字符的个数（包括行末换行符）都不超过100。
　　●除了换行符之外，所有字符都是 ASCII 码 32 至 126 的可打印字符。
　　●每行行首和行末都不会出现空格字符。
　　●输入数据除了 Markdown 语法所需，内容中不会出现 `#`、`*`、`_`、`[`、`]`、`(`、`)`、`<`、`>`、`&` 这些字符。
　　●所有测试点均符合题目所规定的 Markdown 语法，你的程序不需要考虑语法错误的情况。
　　每个测试点包含的语法规则如下表所示，其中“√”表示包含，“×”表示不包含。
    详细见图033.jpg
提示
　　由于本题要将输入数据当做一个文本文件来处理，要逐行读取直到文件结束，C/C++、Java 语言的用户可以参考以下代码片段来读取输入内容。
    见图04.png，05.png，,06.png

*/
