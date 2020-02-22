#include <bits/stdc++.h>

using namespace std;

/*
    ֻ�ܴﵽ70�֣��������ޣ���������������������������������
*/
int n,m;

map<string,string> json;
vector<string> vet;

void trim(string &line){//�˺����ǽ�һ���ַ�������β�ո�ɾ��
	if(!line.empty()){
    	line.erase(0,line.find_first_not_of(" "));
    	line.erase(line.find_last_not_of(" ") + 1);
 	}
}

void clear (string &line){  //�˺����ǽ���б��ȥ������ĿҪ��
	for (int i = 0; i < line.size(); ++i){
		if (line[i] == '\\'){
			line.erase(line.begin() + i);
		}
	}
}

void da_left(string &line){//�˺���Ϊformat�������񣬴����������{
	string line1 = line;
	int s1 = line1.find("{");
	line = "";
	while(s1 != string::npos){
		line1.insert(s1+1,",");
		line += line1.substr(0,s1+1);
		line1.erase(0,s1+1);
		s1 = line1.find("{");
	}
	line += line1;
}

void da_right(){//�˺���Ϊformat�������񣬴����Ҵ�����{����֪ʲôԭ���ô���{���ķ�������}����������Ի���һ�ַ���
	if(vet[vet.size()-1].find("}") != string::npos){
		string s = vet[vet.size()-1];
		s = s.substr(0,s.size()-1);trim(s);
		vet[vet.size()-1] = s;
		da_right();
		vet.push_back("}");
	}
}

void format(string line){//�����淶�ĸ�ʽת��Ϊ��׼��json��ʽ������Ŀ�е�����ģʽ
	trim(line);
	da_left(line);//��������ź���Ӷ��ţ��Ա������һ������
	while(line.find(",") != string::npos){
		int start = line.find(",");
		string s = line.substr(0,start);
		trim(s);vet.push_back(s);
		da_right();//�����Ƕ�������һ�������Խ���ȥ���Ҵ����Ų���
		line.erase(0,start+1);trim(line);
	}
	if(line.size() > 0 && line.find(",") == string::npos){//�������һ��û�ж��ţ�������ֵ�洢
		trim(line);vet.push_back(line);
	}
	da_right();//���һ���洢��ʱ�����һ���Ҵ�����}��ȥ��
}

void deal(){    //���ϸ��json�洢��map��
	for(int i = 0; i < vet.size(); i++){
		if(vet[i] != "" && vet[i] != "{" && vet[i] != "}" && vet[i] != "},"){
			string s = vet[i];
			int split = s.find(":");
			if(split != string::npos){
				string key = s.substr(0,split);trim(key);//��ȡ����
				key = key.substr(1,key.size()-2);//����key��˫����

				string value = s.substr(split+1);trim(value);   //��ȡ����ֵ
				if(value.find("{") == string::npos){    //����������������
					value = value.substr(1,value.size()-2);//����value��˫����
				}
				json[key] = value;//�洢��map��
			}
		}
	}
}



int main(){
	cin >> n >> m;
	cin.get();
	
	string jsonString;
	while(n){//�Ƚ��ַ���ƴ��һ�У�������format�ֿ��������ж�����е�����
		string line;
		getline(cin,line);trim(line);
		if(line != ""){
			jsonString += line;
		}
		n--;
	}
	clear(jsonString);//���ת���ַ�
	format(jsonString); //��һ���ַ�������������ʽ
	deal();         //���ַ���ƥ��浽map�У�һһ��Ӧ


	//���Ը�ʽ��֮���Ƿ���ȷ
	for(int i = 0; i < vet.size(); i++){
		cout << vet[i] << endl;
	}
/*	//�������Ժ�����ֵ�洢֮���Ƿ���ȷ
	for (map<string,string>::iterator iter = json.begin();iter != json.end(); iter++){
        cout << iter->first << "->" << iter->second << endl;
    }
*/
	vector<string> vec;//Ϊ��������룬�洢��vec��
	while(m){
		string s;
		cin >> s;
		
		if(s.find(".") != string::npos){
			string t;
			while(s.find(".") != string::npos){//������
				int start = s.find(".");
				t = s.substr(0,start);
				if(json.find(t) != json.end()){
					s.erase(0,start+1);//��������ϣ���ֻ�������һ��
				}else{
					s = t;//�в���ȷ���ַ��˳��������丳��s;
					break;
				}
			}
			//������ɣ��˳�֮������������ַ��������洢
		}
		
		if(json.find(s) != json.end()){//�ַ��������洢��vector��,������
			if(json[s] == "{"){ //����
				vec.push_back("OBJECT");
			}else{  //�ַ���
				vec.push_back("STRING " + json[s]);
			}
		}else{  //������
			vec.push_back("NOTEXIST");
		}
		m--;
	}
	
	for(int i = 0; i < vec.size(); i++){
		cout << vec[i] << endl;
	}
	return 0;
}

/*=================================================================
1 5
{"firstName": "John","lastName": "Smith","address": {"streetAddress": "2ndStreet","city": {"ddd":""},"state":"NY"},"esc\\aped": "\"hello\""}
firstName
address
address.city.ddd
address.postal
esc\aped
����
11 5
{
"firstName": "John",
"lastName": "Smith",
"address":
{
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.state
address.postal
esc\aped
���
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
=================================================================*/
/*
��������
����JSON (JavaScript Object Notation) ��һ�������������ݽ�����ʽ����������������ṹ�������ݡ�
JSON ��ʽ�еĻ�����Ԫ��ֵ (value)�����ڼ򻯵�Ŀ�ı���ֻ�漰 2 �����͵�ֵ��
����* �ַ��� (string)���ַ�������˫���� " ��������һ���ַ�������Ϊ�գ�������ַ����������г�
��˫���� "����˫����ǰ��ӷ�б�ܣ�Ҳ������ \" ��ʾ��������ַ�б�� \������������б�� \\ ��ʾ��
��б�ܺ��治�ܳ��� " �� \ ������ַ������磺""��"hello"��"\"\\"��
����* ���� (object)��������һ���ֵ�Ե����򼯺ϣ�����Ϊ�գ�����ֵ�Ա�ʾ��������ԣ�������������
ֵ�����Ե����ݡ������������� { ��ʼ���һ����� } ��������ֵ��֮���Զ��� , �ָ���һ����ֵ�Եļ�
��ֵ֮����ð�� : �ָ������������ַ�����ͬһ���������м�ֵ�Եļ���������������ͬ��ֵ�������ַ�����
Ҳ��������һ���������磺{}��{"foo": "bar"}��{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}��
���������ַ����ڲ���λ�ã�����λ�ö����Բ���һ�������ո�ʹ�� JSON �ĳ��ָ������ۣ�Ҳ������һЩ
�ط����У�����Ӱ������ʾ���������ݡ����磬������������һ�� JSON ����Ҳ����д��������ʽ��
����{
����"Mon": "weekday",
����"Tue": "weekday",
����"Sun": "weekend"
����}
��������һ�� JSON ��ʽ���������ݣ��Լ����ɲ�ѯ����̷�����Щ��ѯ�Ľ����
�����ʽ
������һ�������������� n �� m���ֱ��ʾ JSON ���ݵ������Ͳ�ѯ�ĸ�����
���������� n �У�����һ�� JSON ���ݣ���֤������һ���Ϸ��� JSON ����
���������� m �У�ÿ������һ����ѯ������Ҫ��ѯ����������Ҫ�󷵻ض�Ӧ���Ե����ݡ���Ҫ֧�ֶ���ѯ������
��������֮����С���� . ���ӡ���֤��ѯ�ĸ�ʽ���ǺϷ��ġ�
�����ʽ
�������������ÿһ����ѯ����˳�������ѯ�����ÿ�����ռһ�С�
���������ѯ�����һ���ַ���������� STRING <string>������ <string> ���ַ�����ֵ���м���һ���ո�ָ���
���������ѯ�����һ����������� OBJECT������Ҫ�����������ݡ�
���������ѯ��������ڣ������ NOTEXIST��
��������
10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
�������
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
����������ģ��Լ��
����n �� 100��ÿ�в����� 80 ���ַ���
����m �� 100��ÿ����ѯ�ĳ��Ȳ����� 80 ���ַ���
�����ַ����е��ַ���Ϊ ASCII �� 33-126 �Ŀɴ�ӡ�ַ���������ֿո������ַ��������ǿմ���
����������Ϊ�����ַ����������С���� .����ѯʱ���Ĵ�Сд���С�
����50%��������������Ķ���ֻ�� 1 ��ṹ��80%��������������Ķ���ṹ���������� 2 �㡣������˵��{"a": "b"}
��һ��ṹ�Ķ���{"a": {"b": "c"}} �Ƕ���ṹ�Ķ����Դ����ơ�
*/
