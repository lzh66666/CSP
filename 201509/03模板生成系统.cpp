#include <bits/stdc++.h>

/*
    自己比较菜，以下代码超时，只有90分
*/
using namespace std;

int n;
int m;

int main(){
	cin >> m >> n;
	cin.get();
	vector<string> vet;
	string str;
	/*
        输入模板
	*/
	for(int i = 0; i < m; i++){
		getline(cin,str);
		vet.push_back(str);
		vet.push_back("*");			//以便以后换行
	}
	
	/*
        输入替换字符
	*/
	map<string, string> mp;
	for(int i = 0; i < n; i++){
		string word,k,v;
		getline(cin,str);           //保证输入一行后换行
		istringstream line(str);    //输入空格后间断
		line >> word;               //输入第一个空格之前的（即key）
		k = word;
  		while(line >> word){        //双引号之内的空格不应该间断，加一个循环
  			v += word + " ";        //每少一个空格加一个
		}
		v = v.substr(1,v.length()-3);   //去除双引号（-1为正常，-2为减掉上面多余的空格，-3为减掉最后一个双引号）
		mp[k] = v;                  	//存入map中
	}
	
	/*
        替换字符没有大括号，提前定义好
	*/
	string ss1 = "{{ ";
	string ss2 = " }}";

	/*
        进行替换
	*/
	for(int i = 0; i < vet.size(); i++){
		if(vet[i] != "*"){
			string ss = vet[i];         //①先将这行字符串存储
			vet.erase(vet.begin()+i);   //②将这行字符串删除
			/*
                ③先将与替换值相等的进行替换，之前将③和④写到一起，输出结果错误，啊啊啊啊啊啊啊啊啊啊啊啊啊！！！！！！
			*/
			for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
				int k = ss.find(ss1 + it->first + ss2);
				while(k != string::npos){
			    	ss.replace(k,6+it->first.length(),it->second);
					k = ss.find(ss1 + it->first + ss2);
				}
		    }
		    /*
                ④再将要替换但是没有替换值的进行清空
			*/
		    for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
	    		int w = ss.find(ss1);
	    		int t = ss.find(ss2);
	    		while(w != string::npos && t != string::npos){
	    			ss.replace(w,t-w+3,""); //+1为正常，+3为两个大括号（}}）
					w = ss.find(ss1);
			    	t = ss.find(ss2);
 				}
		    }
			vet.insert(vet.begin()+i,ss);   //⑤将修改后的这行字符串在重新插入
		}
	}

	/*
        输出结果
	*/
	//cout << "\n";
	for(int i = 0; i < vet.size(); i++){
		if(vet[i] == "*"){
			cout << "\n";
		}else{
			cout << vet[i];
		}
	}
	/*
	//对存储的替换值进行检验
	cout << "\n";
    for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
    	cout << it->first << "->" << it->second << "\n";
    }
    */
	return 0;
}

/*=================================================================
输入
11 2
<!DOCTYPE html>
<html>
<head>
<title>User {{ name }}</title>
</head>
<body>
<h1>{{ name }}</h1>
<p>Email: <a href="mailto:{{ email }}">{{ email }}</a></p>
<p>Address: {{ address }}</p>
</body>
</html>
name "David Beckham"
email "david@beckham.com"
输出
<!DOCTYPE html>
<html>
<head>
<title>User David Beckham</title>
</head>
<body>
<h1>David Beckham</h1>
<p>Email: <a href="mailto:david@beckham.com">david@beckham.com</a></p>
<p>Address: </p>
</body>
</html>
=================================================================*/
/*
问题描述
　　成成最近在搭建一个网站，其中一些页面的部分内容来自数据库中不同的数据记录，但是页面的基本结构是相同的。例如，
对于展示用户信息的页面，当用户为 Tom 时，网页的源代码是如图03（1）.jpg
	而当用户为 Jerry 时，网页的源代码是如图03（2）.jpg
	这样的例子在包含动态内容的网站中还有很多。为了简化生成网页的工作，成成觉得他需要引入一套模板生成系统。
　　模板是包含特殊标记的文本。成成用到的模板只包含一种特殊标记，格式为 {{ VAR }}，其中 VAR 是一个变量。该标记在
模板生成时会被变量 VAR 的值所替代。例如，如果变量 name = "Tom"，则 {{ name }} 会生成 Tom。具体的规则如下：
　　·变量名由大小写字母、数字和下划线 (_) 构成，且第一个字符不是数字，长度不超过 16 个字符。
　　·变量名是大小写敏感的，Name 和 name 是两个不同的变量。
　　·变量的值是字符串。
　　·如果标记中的变量没有定义，则生成空串，相当于把标记从模板中删除。
　　·模板不递归生成。也就是说，如果变量的值中包含形如 {{ VAR }} 的内容，不再做进一步的替换。
输入格式
　　输入的第一行包含两个整数 m, n，分别表示模板的行数和模板生成时给出的变量个数。
　　接下来 m 行，每行是一个字符串，表示模板。
　　接下来 n 行，每行表示一个变量和它的值，中间用一个空格分隔。值是字符串，用双引号 (") 括起来，内容可包含除双引号
以外的任意可打印 ASCII 字符（ASCII 码范围 32, 33, 35-126）。
输出格式
　　输出包含若干行，表示模板生成的结果。
样例输入
11 2
<!DOCTYPE html>
<html>
<head>
<title>User {{ name }}</title>
</head>
<body>
<h1>{{ name }}</h1>
<p>Email: <a href="mailto:{{ email }}">{{ email }}</a></p>
<p>Address: {{ address }}</p>
</body>
</html>
name "David Beckham"
email "david@beckham.com"
样例输出
<!DOCTYPE html>
<html>
<head>
<title>User David Beckham</title>
</head>
<body>
<h1>David Beckham</h1>
<p>Email: <a href="mailto:david@beckham.com">david@beckham.com</a></p>
<p>Address: </p>
</body>
</html>
评测用例规模与约定
　　0 ≤ m ≤ 100
　　0 ≤ n ≤ 100
　　输入的模板每行长度不超过 80 个字符（不包含换行符）。
　　输入保证模板中所有以 {{ 开始的子串都是合法的标记，开始是两个左大括号和一个空格，然后是变量名，结尾是一个空格和两个右大括号。
　　输入中所有变量的值字符串长度不超过 100 个字符（不包括双引号）。
　　保证输入的所有变量的名字各不相同。
*/
