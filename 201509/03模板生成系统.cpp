#include <bits/stdc++.h>

/*
    �Լ��Ƚϲˣ����´��볬ʱ��ֻ��90��
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
        ����ģ��
	*/
	for(int i = 0; i < m; i++){
		getline(cin,str);
		vet.push_back(str);
		vet.push_back("*");			//�Ա��Ժ���
	}
	
	/*
        �����滻�ַ�
	*/
	map<string, string> mp;
	for(int i = 0; i < n; i++){
		string word,k,v;
		getline(cin,str);           //��֤����һ�к���
		istringstream line(str);    //����ո����
		line >> word;               //�����һ���ո�֮ǰ�ģ���key��
		k = word;
  		while(line >> word){        //˫����֮�ڵĿո�Ӧ�ü�ϣ���һ��ѭ��
  			v += word + " ";        //ÿ��һ���ո��һ��
		}
		v = v.substr(1,v.length()-3);   //ȥ��˫���ţ�-1Ϊ������-2Ϊ�����������Ŀո�-3Ϊ�������һ��˫���ţ�
		mp[k] = v;                  	//����map��
	}
	
	/*
        �滻�ַ�û�д����ţ���ǰ�����
	*/
	string ss1 = "{{ ";
	string ss2 = " }}";

	/*
        �����滻
	*/
	for(int i = 0; i < vet.size(); i++){
		if(vet[i] != "*"){
			string ss = vet[i];         //���Ƚ������ַ����洢
			vet.erase(vet.begin()+i);   //�ڽ������ַ���ɾ��
			/*
                ���Ƚ����滻ֵ��ȵĽ����滻��֮ǰ���ۺ͢�д��һ�����������󣬰�������������������������������������
			*/
			for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
				int k = ss.find(ss1 + it->first + ss2);
				while(k != string::npos){
			    	ss.replace(k,6+it->first.length(),it->second);
					k = ss.find(ss1 + it->first + ss2);
				}
		    }
		    /*
                ���ٽ�Ҫ�滻����û���滻ֵ�Ľ������
			*/
		    for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
	    		int w = ss.find(ss1);
	    		int t = ss.find(ss2);
	    		while(w != string::npos && t != string::npos){
	    			ss.replace(w,t-w+3,""); //+1Ϊ������+3Ϊ���������ţ�}}��
					w = ss.find(ss1);
			    	t = ss.find(ss2);
 				}
		    }
			vet.insert(vet.begin()+i,ss);   //�ݽ��޸ĺ�������ַ��������²���
		}
	}

	/*
        ������
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
	//�Դ洢���滻ֵ���м���
	cout << "\n";
    for (map<string, string>::iterator it = mp.begin(); it != mp.end(); it++){
    	cout << it->first << "->" << it->second << "\n";
    }
    */
	return 0;
}

/*=================================================================
����
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
���
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
��������
�����ɳ�����ڴһ����վ������һЩҳ��Ĳ��������������ݿ��в�ͬ�����ݼ�¼������ҳ��Ļ����ṹ����ͬ�ġ����磬
����չʾ�û���Ϣ��ҳ�棬���û�Ϊ Tom ʱ����ҳ��Դ��������ͼ03��1��.jpg
	�����û�Ϊ Jerry ʱ����ҳ��Դ��������ͼ03��2��.jpg
	�����������ڰ�����̬���ݵ���վ�л��кܶࡣΪ�˼�������ҳ�Ĺ������ɳɾ�������Ҫ����һ��ģ������ϵͳ��
����ģ���ǰ��������ǵ��ı����ɳ��õ���ģ��ֻ����һ�������ǣ���ʽΪ {{ VAR }}������ VAR ��һ���������ñ����
ģ������ʱ�ᱻ���� VAR ��ֵ����������磬������� name = "Tom"���� {{ name }} ������ Tom������Ĺ������£�
�������������ɴ�Сд��ĸ�����ֺ��»��� (_) ���ɣ��ҵ�һ���ַ��������֣����Ȳ����� 16 ���ַ���
�������������Ǵ�Сд���еģ�Name �� name ��������ͬ�ı�����
������������ֵ���ַ�����
�������������еı���û�ж��壬�����ɿմ����൱�ڰѱ�Ǵ�ģ����ɾ����
������ģ�岻�ݹ����ɡ�Ҳ����˵�����������ֵ�а������� {{ VAR }} �����ݣ���������һ�����滻��
�����ʽ
��������ĵ�һ�а����������� m, n���ֱ��ʾģ���������ģ������ʱ�����ı���������
���������� m �У�ÿ����һ���ַ�������ʾģ�塣
���������� n �У�ÿ�б�ʾһ������������ֵ���м���һ���ո�ָ���ֵ���ַ�������˫���� (") �����������ݿɰ�����˫����
���������ɴ�ӡ ASCII �ַ���ASCII �뷶Χ 32, 33, 35-126����
�����ʽ
����������������У���ʾģ�����ɵĽ����
��������
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
�������
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
����������ģ��Լ��
����0 �� m �� 100
����0 �� n �� 100
���������ģ��ÿ�г��Ȳ����� 80 ���ַ������������з�����
�������뱣֤ģ���������� {{ ��ʼ���Ӵ����ǺϷ��ı�ǣ���ʼ������������ź�һ���ո�Ȼ���Ǳ���������β��һ���ո�������Ҵ����š�
�������������б�����ֵ�ַ������Ȳ����� 100 ���ַ���������˫���ţ���
������֤��������б��������ָ�����ͬ��
*/
