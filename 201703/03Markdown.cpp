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
����
# Hello

Hello, world!
���
<h1>Hello</h1>
<p>Hello, world!</p>

����
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
���
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
��������
����Markdown ��һ�ֺ����е�������������ԣ�lightweight markup language�����㷺����׫д����ʽ���ĵ���
������������ı������� Markdown ���﷨д�ɵģ���ͼ031.jpg
��Щ�� Markdown д�ɵ��ı������ܱ����Ǵ��ı���ʽ��Ȼ�����߿��Ժ����׵ؿ��������ĵ��ṹ��ͬʱ�����к�
�๤�߿����Զ��� Markdown �ı�ת���� HTML ���� Word��PDF �ȸ�ʽ��ȡ�ø��õ��Ű�Ч����������������ı�
ͨ��ת���õ��� HTML ������ͼ032.jpg��ʾ��
����Ҫ����������дһ�� Markdown ��ת�����ߣ���� Markdown �ı��� HTML �����ת������������������ⶨ
��� Markdown �﷨�����ת�������������£�
���������飺�������ĵ��Ķ����ṹ������� Markdown �﷨�� 3 �������ʽ���������У�������������֮����һ��
�������зָ������ʱɾ�����зָ�����Ŀ��С�
��������䣺һ������£������������빹��һ�����䡣�����ת���������ڶ���ĵ�һ�����ײ��� `<p>`�������һ
����ĩ���� `</p>`��
��������⣺ÿ����������ֻ��һ�У������ɸ� `#` ��ͷ������һ�������ո�Ȼ���Ǳ������ݣ�ֱ����ĩ��`#` ��
���������˱���ĵȼ���ת��ʱ��`# Heading` ת��Ϊ `<h1>Heading</h1>`��`## Heading` ת��Ϊ `<h2>Heading</h2>`��
�Դ����ơ�����ȼ�����Ϊ 6��
�����������б������б�����������ɣ�ÿ���� `*` ��ͷ������һ�������ո�Ȼ�����б���Ŀ�����֣�ֱ����ĩ��
ת��ʱ�����ʼ����һ�� `<ul>`��������һ�� `</ul>`������ÿ�У�`* Item` ת��Ϊ `<li>Item</li>`�������е�
�����б�ֻ��һ�㣬������������������
���������ڣ����������е����ݣ��������������ڽṹ��
������ǿ����`_Text_` ת��Ϊ `<em>Text</em>`��ǿ���������Ƕ�ף�ÿ���� `_` �ĸ���һ����ż�����Ҳ����������ڡ�
ע�� `_Text_` ��ǰ��һ���ǿո��ַ���
�����𳬼����ӣ�`[Text](Link)` ת��Ϊ `<a href="Link">Text</a>`���������Ӻ�ǿ�������໥Ƕ�ף���ÿ�ָ�ʽ����
����һ�㡣
�����ʽ
������������������ɣ���ʾһ���ñ���涨�� Markdown �﷨׫д���ĵ���
�����ʽ
�����������������ɣ���ʾ����� Markdown �ĵ�ת���ɲ����� HTML ���롣
��������
# Hello

Hello, world!
�������
<h1>Hello</h1>
<p>Hello, world!</p>
����������ģ��Լ��
��������Ĳ��Ե���������������
��������ÿ�����Ե������������������������������100��ÿ���ַ��ĸ�����������ĩ���з�����������100��
��������˻��з�֮�⣬�����ַ����� ASCII �� 32 �� 126 �Ŀɴ�ӡ�ַ���
������ÿ�����׺���ĩ��������ֿո��ַ���
�������������ݳ��� Markdown �﷨���裬�����в������ `#`��`*`��`_`��`[`��`]`��`(`��`)`��`<`��`>`��`&` ��Щ�ַ���
���������в��Ե��������Ŀ���涨�� Markdown �﷨����ĳ�����Ҫ�����﷨����������
����ÿ�����Ե�������﷨�������±���ʾ�����С��̡���ʾ��������������ʾ��������
    ��ϸ��ͼ033.jpg
��ʾ
�������ڱ���Ҫ���������ݵ���һ���ı��ļ�������Ҫ���ж�ȡֱ���ļ�������C/C++��Java ���Ե��û����Բο����´���Ƭ������ȡ�������ݡ�
    ��ͼ04.png��05.png��,06.png

*/
