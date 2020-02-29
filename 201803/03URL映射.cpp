#include <bits/stdc++.h>

using namespace std;

int n,m;
vector<string> vec;//�������

// �տ�ʼ�õ�map��Ϊ���Զ���������������Ĵ���map
typedef  pair<string,string> spair__;
typedef  vector<spair__> vector_type;
vector_type vet;

//�������
bool deal(string key,string path,string value){
	int k=0,p=0;string s;//һ��Ҫ�ǵó�ʼ��0Ŷ
	while(p < path.size() && k < key.size()){
		if(key[k] == path[p]) k++,p++;//��Ϊ��ȫƥ�䣬����һһ�ȶԣ�����������������
		else{
			if(key[k++] != '<') return false;//�����Ϲ���ƥ��ʧ��
			if(key[k] == 'i'){//����int����
				bool judge = false;
                while(isdigit(path[p]) && path[p] != '/'){
                    if(path[p] != '0') judge = true;
					if(judge) s.push_back(path[p]);
					p++;
                }
                if(!judge) return false;
				else s.push_back(' ');//��һ���ո�
                k += 4;//����Ų��int֮��ġ�/��
			}else if(key[k] == 's'){
                bool judge = false;
                while(path[p] && path[p] != '/'){
                    s.push_back(path[p]);
                    p++;judge = true;
                }
                if(!judge) return false;
				else s.push_back(' ');//��һ���ո�
                k += 4;//����Ų��str֮��ġ�/��
            }else if(key[k] == 'p'){//�����path����ֱ�Ӵ洢
            	while(path[p]){
            		s.push_back(path[p]);
            		p++;
				}
				vec.push_back(value + " " + s);
				return true;
			}
		}
	}
	if(p == path.size() && k == key.size()){//ƥ��ɹ�������
		vec.push_back(value + " " + s);
		return true;
	}
	return false;
}

int main(){
	cin >> n >> m;
	while(n){
		string key,value;
		cin >> key >> value;
		vet.push_back(spair__(key,value));//ģ��mapʹ��
		n--;
	}
	
	while(m){
		string path;cin >> path;
		bool judge = false;//�˴�һ��Ҫ��falseд�ϣ�������ʡ�ԣ�ʡ��֮�������⣬������������������
		for(vector_type::iterator iter = vet.begin(); iter != vet.end(); iter++){
  			if(iter->first == path){//û��ӳ�����ֻ�е�ַ����ֱ������������50�֣��е㲻��˼��
				vec.push_back(iter->second);
				judge = true;break;
			}else{//��ӳ�����������ж�
				if(deal(iter->first,path,iter->second)){
					judge = true;break;
				}
			}
		}
		if(!judge) vec.push_back("404");//û��ƥ��ɹ�����¼����
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
/articles/2004/
/articles/hello/
*/
/*=================================================================
����
5 4
/articles/<int>/ year_archive
/articles/2003/ special_case_2003
/articles/<int>/<int>/ month_archive
/articles/<int>/<int>/<str>/ article_detail
/static/<path> static_serve
/articles/2003/
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
