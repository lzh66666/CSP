#include <bits/stdc++.h>

using namespace std;

int p,r,u,q;
vector<string> vet;

int main(){
	
	/*
	    ��һ����
        ˵ʵ������һ�������Ҳ�֪����ʲô���������������ǰ�
        ��ĿҪ�������������������atoi(str.c_str())��stringתint
	*/
	map<string,int> mapp;
	
	cin >> p;
	cin.get();
	for(int i = 0; i < p; i++){
		string str,s,key;
		int value;
		
		getline(cin,str);
		str += ":";
		stringstream ss(str);
		
		getline(ss,s,':');
		key = s;
		
		if(getline(ss,s,':')){
			value = atoi(s.c_str());
		}else{
			value = -1;
		}
		mapp[key] = value;
	}
	
	/*
        �ڶ����֣���Ҫͨ��map<string, map<string,int> >���洢�ڶ�����
        ��������Ȩ��ֻ��һλ�����������ַ�����ͨ��*((str.end()-1))-'0';��
        ��ȡ����
	*/
	
	cin >> r;
	map<string, map<string,int> > mRole;
	for(int i = 0; i < r; i++){
		string role;
		int c;
		map<string,int> m;
		cin >> role >> c;

		while(c){
			string category;
			cin >> category;
			if(category.find(":") != string::npos){
				string level = string(category.begin(),category.end()-2);
				int num = *((category.end()-1))-'0';
				int value = max(num,mRole[role][level]);    //��Ŀ��˵�������ظ�ʱ��Ҫȡ���ֵ
				mRole[role][level] = value;
			}else{
				mRole[role][category] = -1;     //û��Ȩ��ʱ������-1����ʾû��Ȩ��
			}
			c--;
		}
	}
	
	/*
        �������֣���Ҫͨ��map<string, vector<string> >���洢��һ����������ж����ɫ
        ����valueֵͨ��vector���洢��
	*/
	cin >> u;
	map<string, vector<string> > mUser;
	for(int i = 0; i < u; i++){
		string name;
		int c;
		cin >> name >> c;
		while(c){
			string role;
			cin >> role;
			mUser[name].push_back(role);
			c--;
		}
	}
	
	
	/*
        ���Ĳ�����ͨ����ǰ��ڶ����ֺ͵������ִ���ƥ��֮��
        ��true��false�����ִ���vector�У�һ��������
        �Ե�һ������˵��
	*/
	cin >> q;
	for(int i = 0; i < q; i++){
		string name;
		cin >> name;
		if(mUser.count(name) > 0){      //��������name����Ҫ�󣬼��û�map���д��û����ɼ���������ֱ�Ӵ洢false
			string category,value;
			int num = -1;
			cin >> category;           
			if(category.find(':') != string::npos){ //�����ѯ���û�Ȩ�ޣ����value��num��ֵ
				value = string(category.begin(),category.end()-2);
				num = *(category.end()-1)-'0';
			}else{
				value = category;
			}
			
			bool judge = false;
			int numm = -1;
			
			for(int j = 0; j < mUser[name].size(); j++){        //�������û��еĽ�ɫ�����ܲ�ֹһ�������Ա������磺alice
				string role = mUser[name][j];           //���ôεĽ�ɫ����ȡ�������磺hr
				for(map<string,int>::iterator it = mRole[role].begin(); it != mRole[role].end(); it++){//������ɫ��hr����ӵ�еĵ�Ȩ��
					if(it->first == value){ //��hr�����ڵ�Ȩ�����������value��ȲŽ����ж�
						if(num == -1){      //��ʱ˵����û��Ȩ�޲�ѯ����û�У��Ĳ�ѯ
							numm = max(numm,it->second);//ȡ�����û���ӵ�еĽ�ɫ�и���Ȩ����ߵ���һ��
							judge = true;
						}else{               //��ʱ˵������Ȩ�޲�ѯ��num��ֵ
							if(it -> second >= num){    //�����û��Ľ�ɫ��Ȩ�޸��������Ȩ�޵�ʱ�򣬱��Ϊtrue
								judge = true;
							}
						}
					}
				}
			}
			if(!judge){     //���û�û�и���Ȩ��
				vet.push_back("false");
			}else{
				if(num != -1){  //�������Ȩ�޲�ѯ�����������
					vet.push_back("true");
				}else{                  //û��Ȩ�޲�ѯҲ���������
					if(numm == -1){     //1.˵������Ȩ��û�еȼ����϶�����
						vet.push_back("true");
					}else{              //2.����Ȩ���еȼ���������ý�ɫ��ӵ�еĵ���ߵȼ�
						/*����ͨ��stream������תΪ�ַ���*/
						stringstream stream;string st;
						stream << numm;stream >> st;
						vet.push_back(st);
					}
				}
			}
		}else{      //û�д��û����洢false
			vet.push_back("false");
		}
	}
	
	/*
        ���
	*/
	
	for(int i = 0; i < vet.size(); i++){
		cout << vet[i] << endl;
	}
	
	return 0;
}

/*=================================================================
����
3
crm:2
git:3
game
4
hr 1 crm:2
it 3 crm:1 git:1 game
dev 2 git:3 game
qa 1 git:2
3
alice 1 hr
bob 2 it qa
charlie 1 dev
9
alice game
alice crm:2
alice git:0
bob git
bob poweroff
charlie game
charlie crm
charlie git:3
malice game
���
false
true
false
2
false
true
false
true
false
=================================================================*/
/*
��������
������Ȩ (authorization) �Ǹ���ҵ��ϵͳ����ȱ�ٵ���ɲ��֣�ϵͳ�û�ͨ����Ȩ���ƻ��ϵͳ�и���ģ��Ĳ���Ȩ�ޡ�
���������е���Ȩ������������Ƶģ�ÿλ�û��������ɽ�ɫ��ÿ�ֽ�ɫ��������Ȩ�ޡ����磬�û� david ���� manager ��ɫ��
manager ��ɫ�� crm:2 Ȩ�ޣ����û� david ���� crm:2 Ȩ�ޣ�Ҳ���� crm ��Ȩ�޵ĵ� 2 �ȼ���Ȩ�ޡ�
��������أ��û����ͽ�ɫ���ƶ�����Сд��ĸ��ɵ��ַ��������Ȳ����� 32��Ȩ�޷�Ϊ�ֵȼ�Ȩ�޺Ͳ��ֵȼ�Ȩ�������ࡣ��
�ȼ�Ȩ����Ȩ��������Ȩ�޵ȼ����ɣ��м���ð�š�:���ָ�������Ȩ������Ҳ����Сд��ĸ��ɵ��ַ��������Ȳ����� 32��Ȩ��
�ȼ���һλ���֣��� 0 �� 9������Խ���ʾȨ�޵ȼ�Խ�ߡ�ϵͳ�涨����û�����ĳ��ĳһ�ȼ���Ȩ�ޣ���ô��Ҳ���Զ����и�
����͵ȼ���Ȩ�ޡ�����������������У��� crm:2 �⣬�û� david Ҳ���� crm:1 �� crm:0 Ȩ�ޡ����ֵȼ�Ȩ��������Ȩ��ʱ
ֻ��Ȩ��������û��Ȩ�޵ȼ���Ҳû�����ڷָ���ð�ţ���
��������ϵͳ���û�����ɫ��Ȩ�޵�������Ϣ����ĳ�����Ҫ�ش��������û���Ȩ�޵Ĳ�ѯ����ѯ�ɷ�Ϊ���¼��ࣺ
����* ���ֵȼ�Ȩ�޵Ĳ�ѯ�����Ȩ�ޱ����ǲ��ֵȼ��ģ����ѯʱ��ָ���ȼ��������Ƿ���и�Ȩ�ޣ�
����* �ֵȼ�Ȩ�޵Ĵ��ȼ���ѯ�����Ȩ�ޱ���ֵȼ�����ѯҲ���ȼ����򷵻��Ƿ���и���ĸõȼ�Ȩ�ޣ�
����* �ֵȼ�Ȩ�޵Ĳ����ȼ���ѯ�����Ȩ�ޱ���ֵȼ�����ѯ�����ȼ����򷵻ؾ��и���Ȩ�޵ĵȼ�����������и�����κεȼ�
Ȩ�ޣ��򷵻ء��񡱡�
�����ʽ
���������һ����һ�������� p����ʾ��ͬ��Ȩ�����������������ŵ� p �б���Ϊ P �Σ�ÿ��һ���ַ�������������Ȩ�ޡ����ڷ�
�ȼ�Ȩ�ޣ���ʽΪ <category>:<level>������ <category> ��Ȩ��������<level> �Ǹ���Ȩ�޵���ߵȼ������ڲ��ֵȼ�Ȩ�ޣ��ַ�
��ֻ����Ȩ��������
����������һ����һ�������� r����ʾ��ͬ�Ľ�ɫ�����������ŵ� r �б���Ϊ R �Σ�ÿ������һ�ֽ�ɫ����ʽΪ
����<role> <s> <privilege 1> <privilege 2> ... <privilege s>
�������� <role> �ǽ�ɫ���ƣ�<s> ��ʾ�ý�ɫ���ж�����Ȩ�ޡ����� <s> ���ַ��������ý�ɫ���е�Ȩ�ޣ���ʽͬ P �Ρ�
����������һ����һ�������� u����ʾ�û������������ŵ� u �б���Ϊ U �Σ�ÿ������һ���û�����ʽΪ
����<user> <t> <role 1> <role 2> ... <role t>
�������� <user> ���û�����<t> ��ʾ���û����ж����ֽ�ɫ������ <t> ���ַ����������û����еĽ�ɫ��
����������һ����һ�������� q����ʾȨ�޲�ѯ�������������ŵ� q �б���Ϊ Q �Σ�ÿ������һ����Ȩ��ѯ����ʽΪ <user> <privilege>��
��ʾ��ѯ�û� <user> �Ƿ���� <privilege> Ȩ�ޡ������ѯ��Ȩ���Ƿֵȼ�Ȩ�ޣ����ѯ�е� <privilege> ��ָ���ȼ�����ʾ��ѯ���û�
�Ƿ���иõȼ���Ȩ�ޣ�Ҳ���Բ�ָ���ȼ�����ʾ��ѯ���û����и�Ȩ�޵ĵȼ������ڲ��ֵȼ�Ȩ�ޣ�ֻ�ܲ�ѯ���û��Ƿ���и�Ȩ�ޣ���ѯ
�в���ָ���ȼ���
�����ʽ
��������� q �У�ÿ��Ϊ false��true������һ�����֡�false ��ʾ��Ӧ���û���������Ӧ��Ȩ�ޣ�true ��ʾ��Ӧ���û�������Ӧ��Ȩ�ޡ�
���ڷֵȼ�Ȩ�޵Ĳ����ȼ���ѯ���������Ȩ�ޣ�������һ�����֣���ʾ���û����и�Ȩ�޵ģ���ߣ��ȼ�������û������ڣ����߲�ѯ��
Ȩ��û�ж��壬��Ӧ�÷��� false��
��������
3
crm:2
git:3
game
4
hr 1 crm:2
it 3 crm:1 git:1 game
dev 2 git:3 game
qa 1 git:2
3
alice 1 hr
bob 2 it qa
charlie 1 dev
9
alice game
alice crm:2
alice git:0
bob git
bob poweroff
charlie game
charlie crm
charlie git:3
malice game
�������
false
true
false
2
false
true
false
true
false
����˵��
�����������������ĳ����У������û�ʵ�ʵ�Ȩ�����£�
����* �û� alice ���� crm:2 Ȩ��
����* �û� bob ���� crm:1��git:2 �� game Ȩ��
����* �û� charlie ���� git:3 �� game Ȩ��
����* �û� malice δ��������˲������κ�Ȩ��
����������ģ��Լ��
��������������ģ��
����* 1 �� p, r, u �� 100
����* 1 �� q �� 10?000
����* ÿ���û����еĽ�ɫ�������� 10��ÿ�ֽ�ɫ���е�Ȩ�����಻���� 10
����Լ����
����* ���뱣֤�Ϸ��ԣ�������
����1) ��ɫ��Ӧ��Ȩ���б�R �Σ��е�Ȩ�޶���֮ǰ��P �Σ����ֹ��ģ�Ȩ�޿����ظ����֣�������ȼ���Ȩ���ظ����֣��Եȼ���ߵ�Ϊ׼
����2) �û���Ӧ�Ľ�ɫ�б�U �Σ��еĽ�ɫ����֮ǰ��R �Σ����ֹ��ģ���������ɫ������ĳһ�ֵȼ�Ȩ�ޣ��Եȼ���ߵ�Ϊ׼
����3) ��ѯ��Q �Σ��е��û�����Ȩ����������֤��֮ǰ��U �κ� P �Σ����ֹ�
����* ǰ 20% ����������ֻ��һ�ֽ�ɫ
����* ǰ 50% ����������Ȩ�޶��ǲ��ֵȼ��ģ���ѯҲ�������ȼ�
*/
