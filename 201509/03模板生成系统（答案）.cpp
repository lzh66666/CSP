#include <bits/stdc++.h>
using namespace std;

/*
    ���´���Ϊ��׼�𰸣��������Լ���д
*/

vector<string>text;
string key,val;
map<string,string> dict;

int main() {
    int n,m;
    string str;
    cin >> n >> m;
    cin.get();//�Ե����з�
    
    for(int i = 0; i < n; i++) {
        getline(cin,str);
        text.push_back(str);
    }
    
    for(int i = 0; i < m; i++) {
        cin >> key;
        getline(cin,val);
        dict[key] = val.substr(2,val.size()-3);
    }
    
    //�滻�ַ��������
    for(int i=0; i<n; i++) {
        int pre=0,next;
        while(1) {
            //string��find(s,pre)��ʾ���±�Ϊpre��λ�ò����ַ�������δ�ҵ�����-1
            if((pre = text[i].find("{{ ",pre))==-1) break;
            if((next = text[i].find(" }}",pre))==-1) break;//���ҵ�һ��pre,��pre�����"}}"
            key=text[i].substr(pre+3,next-pre-3);	//��{{     }}����ַ���key���
            text[i].replace(pre,next-pre+3,dict.count(key) ? dict[key] : "");//�滻
            pre += dict.count(key) ? dict[key].size() : 0;//�����ظ��滻
        }
        cout << text[i] << endl;
    }
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
