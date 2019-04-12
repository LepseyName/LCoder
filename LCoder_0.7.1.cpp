/*
	Ýòà ïðîãðàììà-øèôðîâàëüùèê, ìåíÿåò áèòû â áàéòàõ ïî åäð¸íàìó çàêîíó, çàâèñÿùåìó îò òð¸õ öèôð. Ìîæíî çàäàòü íåñêîëüêî óðîâíåé øèôðîâàíèÿ.
	UP. Òåïåðü ïðîñòî ìåíÿåì ñèìâîë ïî ìàòåìàòè÷åñêîé ôîðìóëå áåç èñïîëüçîâàíèÿ áèòîâ.
*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<ctime>

#define CODER "-c"													//Êëþ÷ øèôðîâêè
#define DECODER "-d"												//Êëþ÷ äåøèôðîâêè
#define KEY_SIZE 120												//Ìàêñèìàëüíàÿ äëèííà ñåêðåòíîãî êîäà
#define NAME_SIZE 50												//Ìàêñèìàëüíàÿ äëèííà íàçâàíèé ôàéëîâ
#define STD_NAME "0"
#define STD_EXTEN ".sec"
using namespace std;

char shifr(char ,unsigned char , unsigned char , unsigned char , unsigned char , unsigned char ,bool );
char menu();
char* KEY_check (char*, bool);
char* KEY_enter (char );
void cin_clear();
void report(char , char* , char* , char*, time_t , size_t );
time_t encryption(istream& ,ostream&, size_t& ,char*, bool , bool );

int main(int argc, char* argv[]){
	fstream in, out;																						//����� ����� ������
    char *name_in = 0,																						//��� �������� �����
		 *name_out= 0,																						//��� ��������� �����
		 *KEY     = 0,																						//����
		  men = 0;																							//�������� ����
    bool coder = true,																						//���� �������� / ����������
		 print = true;																						//���� ������ ������������ ����
    size_t file_size=0;																						//������ �����
	// ������������ �������������� �������
	if(argc>1){
		name_in = new char[strlen(argv[1]) + 1];															//1 ������� - ������� ����
		strcpy(name_in, argv[1]);
		if(argc>2){
			name_out = new char[strlen(argv[2]) + 1];														//2 ������� - �������� ����
			strcpy(name_out, argv[2]);
			if(argc>3){
				if (strcmp(argv[3],CODER)==0) men='1';														//���� ����� ����� / �������
				else if (strcmp(argv[3],DECODER)==0) men='2';												// ����� ������� ����������
				else cout<<"LCoder <input_file> <output_file> <"<<CODER<<" (coder) or "<<DECODER<<" (decoder)> <KEY>\n";
				if(argc>4){
					KEY  =new char[strlen(argv[4]) + 1];													//4 ������� - ����
					strcpy(KEY, argv[4]);
					if(men) print = false;																	//���� ��� �������� ������� �������,
				}																							//�� �� ����� ������
			}
		}
	}
	
	if (print) cout<<"____________________LCoder v_0.7.1_______________________\n";							//�����������
	
    if(!men){																								//���� �� ���� � ���������� ������� 
    	men=menu();
    	if(men=='3')return 0;
	}
	if(men=='2') coder=false;																				//������������� ���������� � ����� �������������
	
    while(1){																								//�������� �������� �����
        if(!name_in) {																						//���� ����� �� ���� � �������
			cout<<"Enter a name input file: ";																//������� ��� �����
			name_in = new char[NAME_SIZE];
			cin.getline(name_in, NAME_SIZE);
        	
			if(cin.fail()){																					//� �������� �� ������
        		cout<<"\n_______________________invalide input1_________________\n\n";						
        		cin_clear();
				delete [] name_in;																			//� ������� ������ ��������
				name_in = 0; 
        		continue;
			}
		}
        
        in.open(name_in, ios::in /*| ios::nocreat*/ |ios:: binary);											//�������� �����
        
		if (in) break;																						//���� �� ������ �������
        else{
        	print = true;																					//����� �������� ��������� 
        	cout<<"\n_______________________invalide name1__________________\n\n";
			delete [] name_in;																					//� ������� ������ ��������
			name_in = 0;
		}  
    }
    if (print) cout<<"\n------------------ input file open! -------------------\n\n";	
    
    while(1){																								//�������� ��������� �����
        if(!name_out){																						//���� ����� �� ���� � �������
			cout<<"Enter a name output file: ";
			name_out = new char[NAME_SIZE];
			cin.getline(name_out, NAME_SIZE);																//������� ��� �����
			
			if(cin.fail()){																					//� �������� �� ������
	    		cout<<"\n_______________________invalide input2_________________\n\n";
	    		cin_clear(); 
	    		delete [] name_out;
	    		name_out = 0;
	    		continue;
			} 
		}
			
		if (strcmp(name_out,STD_NAME)==0) {																//��������� ��� �� �����������
    		if(men=='1'){																					//��� �����������
				delete name_out;
				name_out = new char[strlen(name_in) + strlen(STD_EXTEN) + 1];
				strcpy(name_out,name_in);																	//�������� ������� ���
				strcat(name_out,STD_EXTEN);																	//� ���������� ����������
			}
    		else  																							//��� �������������
				if(strcmp( STD_EXTEN, name_in + (strlen(name_in) - strlen(STD_EXTEN)) )==0){				//��������� ��������� ������� ������
					delete [] name_out;
					name_out = new char[strlen(name_in) + 1];
					strcpy(name_out,name_in);																//���� �� �� �������� � �������� ��� ��������� ���
					name_out[strlen(name_out)-strlen(STD_EXTEN)]='\0';										//� �������� �� ����������
				}
    		else {																							//���� ��� �� �����������
				print = true;																				// ������� ��������� � ���� ��� �������
	    		delete [] name_out;
	    		name_out = 0;
				cout<<"\n_______________________not standart name_______________\n\n";
	    		continue;
			}
		}  
		   
        out.open(name_out, ios::out | ios::trunc | ios:: binary);											//�������� �����
        
		if (out) break;																						//���� �� ������ �������
        else{
        	print = true;																					//����� �������� ��������� 
        	cout<<"\n_______________________invalide name2__________________\n\n";
			delete [] name_out;																				//� ������� ������ ��������
			name_out = 0;
		}
    }
    if (print) cout<<"\n------------------ output file open! ------------------\n\n"; 
    
    if(KEY && !KEY_check(KEY,false)){
    	
    	if(men=='1' && strlen(KEY)==1 && KEY[0]>'0' && KEY[0]<='5') KEY = KEY_enter(KEY[0]);
    	else {
    		delete [] KEY;
    		KEY = 0;
		}
	}
																					//� ���� ������ ������� ��������� ���� �� ������������
    if(!KEY){																								//���� ����� ��� ��� �� �� ����������
    	print = true;																						//����� ���������
		if(men=='2'){																						//���� ������������  
	    	KEY = KEY_enter('0');																			//�� ����� ����� ���
	    }
	    else while(1){																						//���� ����������
	            char ch;
	            cout<<"Enter level a coder( 1-5) or 0 for enter personal cod: ";          					//���������� ������� ���������� 
	            cin.get(ch);
	            cin_clear();
	            if(ch>='0' && ch<='5'){																		//��������� �� �������
					KEY = KEY_enter(ch);																	//������ ���
					break;
				}
				cout<<"\n_______________________invalide number_________________\n\n";						//�������� � ������
	        }
	}
	
	time_t times=encryption(in, out, file_size, KEY, coder, print);											//������� � �������� �� ������� ����� ������
	in.close();																								//��������� �����
	out.close();
	if(print) report(men,name_in,name_out, KEY, times,file_size);											//������� ����������
    else if (men=='1') cout<<KEY<<'\n';
    
	delete [] KEY;
	delete [] name_in;
	delete [] name_out;
	return 0;
}

void cin_clear(){	cin.clear(); while(cin.get()!='\n'); }

																											//������� ������ 
char shifr(char ch, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char p_z, bool coder=true){

	int gamma = (int)( p_z*(a + b*d  + d*a ) - a*b - c*d);													//������ �����
	
	int sm = p_z*(11.0/255.0) + 5;																			//������ �������� � �������(�������������) �����
	gamma = (gamma>>sm) | (gamma<<sm);
	
	gamma = (char)(gamma ) + (char)(gamma>>24) - (char)(gamma>>16) + (char)(gamma>>8) ;						//������ ����� � char ������� �������������

	if(coder) ch+= gamma;																					//����������� ��� ������� �����
	else  	  ch-= gamma;

	return ch;
}

char menu(){																								//���� ����������
	char b='0';
    while(!(b>='1' && b<='3')){
        cout<<"Enter 1 for coder\n";
        cout<<"Enter 2 for decoder\n";
        cout<<"Enter 3 for exit\n";
        cin.get(b);
        cin_clear();   						  //Error!!!!
	}
	return b;
}

char* KEY_check(char* KEY, bool print = true){
	if(KEY){
		int len = strlen(KEY);
		
		if( len % (KEY_SIZE/5)!=0 || len<1 || len>KEY_SIZE){
			if(print) cout<<"Invalide KEY!The KEY must be a multiple of 24 characters and must be between 24 and 120 characters long\n";
			return 0;
		}
	}
	return KEY;
}

char* KEY_enter (char ch){																					//���� �����
	char *KEY = 0;
    if(ch=='0')	while(1){																					//����� 0 - ������ ����
			        cout<<"Enter KEY(max length "<<KEY_SIZE<<" ): ";
			        KEY = new char[KEY_SIZE + 1];
			        cin.getline(KEY, KEY_SIZE + 1);
			        if(cin.fail()){																			//��������� �� ������
			        		cout<<"\n_______________________invalide KEY____________________\n\n";
			        		cin_clear(); 
			        		continue;
					}
					if(KEY_check(KEY))break;																//��������� ������������ �������� �����
					delete [] KEY;				
				}
    else{																									//������ 1 2 3 4 5 - �������������� ��������� �����
    	srand(time(NULL));
        int coder=(KEY_SIZE/5) * ( (int)ch -48);															//��������� ������ �����
        
		KEY = new char[coder + 1];
        char *start_KEY = KEY;
        
		while(coder--)   *(KEY++)=(char)(rand()%94+32);														//��������� ���� �� ������� � ����-�����������
        *KEY='\0';
        
        KEY = start_KEY;																					//�������������� ����
    }
    return KEY;
}

time_t encryption(istream &in,ostream &out, size_t &file_size,char* KEY, bool coder, bool print){
	time_t start = time(NULL);
	char a, b, c, d, ch;
	int num, num_buf=strlen(KEY);
	size_t peek=0,prozent;
	
	in.seekg(0,ios::end);
	file_size=in.tellg();
	in.seekg(0,ios::beg);
	prozent=file_size/54;
	
    if (print) cout<<"[";
	while(1){	
		in.get(ch);
		peek++;
		num=0;
		if (print) if(prozent)if (peek%prozent==0) cout<<"#";
		while(num<num_buf){
    		a=KEY[num++];
    		b=KEY[num++];
    		c=KEY[num++];
    		d=KEY[num++];
			ch=shifr(ch,a,b,c,d,(char)(file_size%peek),coder);
    	}
		if(!in.eof())out.put(ch);
		else break;    		
	}
	if (print) cout<<"#]\n";    
	return time(NULL)-start;
}
void report(char men,char* name_in,char* name_out, char *KEY, time_t times,size_t file_size){
	cout<<"__________________________\\0-0/________________________\n";
    if(men=='1') cout<<"-------------------------------------------------------\nYou KEY is: ["<<KEY<<"]\n-------------------------------------------------------\n";
    if (men=='1') cout<<"  Coder: ";else cout<<"Decoder: ";cout<<'['<<name_in<<"]\n";
	cout<<"In file: "<<'['<<name_out<<"]\n";
	cout<<"Filesiz: "<<file_size<<" byt\n";
	cout<<"Time: "<<times<<" s\n";
	cout<<"\t\tLepseyName\n";
    
    cin.get();
}
