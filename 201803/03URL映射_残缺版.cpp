#include <bits/stdc++.h>

using namespace std;

int n,m;
map<string,string> pMap;
vector<string> vec;
  
bool deal(string key,string path){
	int k=0,p=0;string s;//һ��Ҫ�ǵó�ʼ��0Ŷ
	while(p < path.size() && k < key.size()){
		if(key[k] == path[p]){
			k++;p++;
		}else{
			if(key[k++] != '<'){
				return false;
			}
			if(key[k] == 'i'){
				bool judge = false;
                while(true){
                    if(path[p] >= '0' && path[p] <= '9'){
                        if(path[p] == '0' && !judge){
                        	path.erase(path.begin()+p);
                        	p--;
						}else{
							judge = true;
							s.push_back(path[p]);
						}
						p++;
                    }else{
						break;
                    }
                }
                if(!judge || path[p] != '/'){
                	return false;
				}else{
					s.push_back(' ');
				}
                k += 4;
			}else if(key[k] == 's'){
                bool judge = false;
                while(path[p] && path[p] != '/'){
                    judge = true;
                    s.push_back(path[p]);
                    p++;
                }
                if(!judge){
                	return false;
				}else{
					s.push_back(' ');
				}
                k += 4;
            }else if(key[k] == 'p'){
            	while(path[p]){
            		s.push_back(path[p]);
            		p++;
				}
				vec.push_back(pMap[key] + " " + s);
				return true;
			}
		}
	}
	if(p == path.size() && k == key.size()){
		vec.push_back(pMap[key] + " " + s);
		return true;
	}
	return false;
}



int main(){
	cin >> n >> m;
	
	while(n){
		string key,value;
		cin >> key >> value;
		pMap[key] = value;
		n--;
	}
	
	while(m){
		string path;cin >> path;
		bool judge = false;
  		for(map<string,string>::iterator iter = pMap.begin(); iter != pMap.end(); iter++){
  			if(iter->first == path){
				vec.push_back(iter->second);
				judge = true;break;
			}else{
				if(deal(iter->first,path)){
					judge = true;break;
				}
			}
		}
		if(!judge){
			vec.push_back("404");
		}
		m--;
	}
	
	for(int i = 0; i < vec.size(); i++){
		cout << vec[i] << endl;
	}
	return 0;
}
/*
5 2
/articles/2003/ special_case_2003
/articles/<int>/ year_archive
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2003/
/articles/hello/
*/
/*=================================================================
����
5 4
/articles/2003/ special_case_2003
/articles/<int>/ year_archive
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2004/
/articles/1985/09/aloha/
/articles/hello/
/static/js/jquery.js
���
year_archive 2004
article_detail 1985 9 aloha
404
static_serve js/jquery.js
=================================================================*/
/*
��������
����URL ӳ�������� Django��Ruby on Rails ����ҳ��� (web frameworks) ��һ����Ҫ��������ڴ������������ HTTP ����
URL ӳ��ģ�����������е� URL ��ַ����������ɸ���Ӧ�Ĵ�����롣���ڣ�������ʵ��һ���򵥵� URL ӳ�书�ܡ�
���������� URL ӳ�书�ܵ������������� URL ӳ�������ɡ���һ�����󵽴�ʱ��URL ӳ�书�ܻὫ�����е� URL ��ַ������
�õ��Ⱥ�˳����һ����Щ�������ƥ�䡣��������һ����ȫƥ��Ĺ���ʱ��ƥ��ɹ����õ�ƥ��Ĺ����Լ�ƥ��Ĳ�����������
ƥ���κ�һ��������ƥ��ʧ�ܡ�
������������� URL ��ַ����б�� / ��Ϊ�ָ�����·������֤��б�ܿ�ͷ�������Ϸ��ַ���������СдӢ����ĸ�����������֡�
���� -���»��� _ ��С���� .�����磬/person/123/ ��һ���Ϸ��� URL ��ַ���� /person/123? �򲻺Ϸ������ڲ��Ϸ����ַ�
�ʺ� ?�������⣬Ӣ����ĸ���ִ�Сд����� /case/ �� /CAse/ �ǲ�ͬ�� URL ��ַ��
�������� URL ӳ�����ͬ������б�ܿ�ʼ�����˿����������� URL ��ַ�⣬�����԰��������������� 3 �֣�
�����ַ��� <str>������ƥ��һ���ַ�����ע���ַ����ﲻ�ܰ���б�ܡ����磬abcde0123��
�������� <int>������ƥ��һ���������ŵ�������ȫ���ɰ�����������ɡ����磬01234��
����·�� <path>������ƥ��һ���ַ������ַ������԰���б�ܡ����磬abcd/0123/��
�������� 3 �ֲ���������ƥ��ǿյ��ַ���������������Ŀ�涨������ <str> �� <int> ǰ��һ����б�ܣ�����Ҫô��б�ܣ�
Ҫô�ǹ���Ľ�����Ҳ���Ǹò����ǹ�������һ���֣����� <path> ��ǰ��һ����б�ܣ�����һ���ǹ���Ľ����������� URL
��ַ���ǹ��򣬶��������������б�ܡ�
�����ʽ
���������һ�������������� n �� m���ֱ��ʾ URL ӳ��Ĺ��������ʹ������ URL ��ַ�������м���һ���ո��ַ��ָ���
������ 2 ������ n+1 �а�ƥ����Ⱥ�˳������ URL ӳ������������Ϣ���� i+1 �а��������ַ��� pi �� ri������ pi ��ʾ
 URL ƥ��Ĺ���ri ��ʾ���� URL ƥ������֡������ַ������ǿգ��Ҳ������ո��ַ��������м���һ���ո��ַ��ָ���
������ n+2 ������ n+m+1 ������������� URL ��ַ���� n+1+i �а���һ���ַ��� qi����ʾ������� URL ��ַ���ַ����в���
���ո��ַ���
�����ʽ
�������빲 m �У��� i �б�ʾ qi ��ƥ���������ƥ��ɹ�����ƥ���˹��� pj ���������Ӧ�� rj��ͬʱ������������в�����
����ͬһ�����������ƥ���Ĳ�����ע�������������ʱҪ��ǰ����ȥ������������֮����һ���ո��ַ��ָ������ƥ��ʧ�ܣ�
����� 404��
��������
5 4
/articles/2003/ special_case_2003
/articles/<int>/ year_archive
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2004/
/articles/1985/09/aloha/
/articles/hello/
/static/js/jquery.js
�������
year_archive 2004
article_detail 1985 9 aloha
404
static_serve js/jquery.js
����˵��
�������ڵ� 1 ����ַ /articles/2004/���޷�ƥ��� 1 �����򣬿���ƥ��� 2 �����򣬲���Ϊ 2004��
�������ڵ� 2 ����ַ /articles/1985/09/aloha/��ֻ��ƥ��� 4 �����򣬲�������Ϊ 1985��9���Ѿ�ȥ��ǰ���㣩�� aloha��
�������ڵ� 3 ����ַ /articles/hello/���޷�ƥ���κ�һ������
�������ڵ� 4 ����ַ /static/js/jquery.js������ƥ�����һ�����򣬲���Ϊ js/jquery.js��
���ݹ�ģ��Լ��
����1 �� n �� 100��1 �� m �� 100��
�������������еĳ��Ȳ����� 100 ���ַ������������з�����
������֤����Ĺ����ǺϷ��ġ�

*/
