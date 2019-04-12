/*
	ГќГІГ  ГЇГ°Г®ГЈГ°Г Г¬Г¬Г -ГёГЁГґГ°Г®ГўГ Г«ГјГ№ГЁГЄ, Г¬ГҐГ­ГїГҐГІ ГЎГЁГІГ» Гў ГЎГ Г©ГІГ Гµ ГЇГ® ГҐГ¤Г°ВёГ­Г Г¬Гі Г§Г ГЄГ®Г­Гі, Г§Г ГўГЁГ±ГїГ№ГҐГ¬Гі Г®ГІ ГІГ°ВёГµ Г¶ГЁГґГ°. ГЊГ®Г¦Г­Г® Г§Г Г¤Г ГІГј Г­ГҐГ±ГЄГ®Г«ГјГЄГ® ГіГ°Г®ГўГ­ГҐГ© ГёГЁГґГ°Г®ГўГ Г­ГЁГї.
	UP. Г’ГҐГЇГҐГ°Гј ГЇГ°Г®Г±ГІГ® Г¬ГҐГ­ГїГҐГ¬ Г±ГЁГ¬ГўГ®Г« ГЇГ® Г¬Г ГІГҐГ¬Г ГІГЁГ·ГҐГ±ГЄГ®Г© ГґГ®Г°Г¬ГіГ«ГҐ ГЎГҐГ§ ГЁГ±ГЇГ®Г«ГјГ§Г®ГўГ Г­ГЁГї ГЎГЁГІГ®Гў.
*/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<ctime>

#define CODER "-c"													//ГЉГ«ГѕГ· ГёГЁГґГ°Г®ГўГЄГЁ
#define DECODER "-d"												//ГЉГ«ГѕГ· Г¤ГҐГёГЁГґГ°Г®ГўГЄГЁ
#define KEY_SIZE 120												//ГЊГ ГЄГ±ГЁГ¬Г Г«ГјГ­Г Гї Г¤Г«ГЁГ­Г­Г  Г±ГҐГЄГ°ГҐГІГ­Г®ГЈГ® ГЄГ®Г¤Г 
#define NAME_SIZE 50												//ГЊГ ГЄГ±ГЁГ¬Г Г«ГјГ­Г Гї Г¤Г«ГЁГ­Г­Г  Г­Г Г§ГўГ Г­ГЁГ© ГґГ Г©Г«Г®Гў
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
	fstream in, out;																						//Файлы входа выхода
    char *name_in = 0,																						//Имя входного файла
		 *name_out= 0,																						//Имя выходного файла
		 *KEY     = 0,																						//Ключ
		  men = 0;																							//Значение меню
    bool coder = true,																						//флаг шифровки / дешифровки
		 print = true;																						//флаг вывода декоративной инфы
    size_t file_size=0;																						//Размер файла
	// Максимальная иформативность консоли
	if(argc>1){
		name_in = new char[strlen(argv[1]) + 1];															//1 элемент - входной файл
		strcpy(name_in, argv[1]);
		if(argc>2){
			name_out = new char[strlen(argv[2]) + 1];														//2 элемент - выходной файл
			strcpy(name_out, argv[2]);
			if(argc>3){
				if (strcmp(argv[3],CODER)==0) men='1';														//Ищем ключи кодер / декодер
				else if (strcmp(argv[3],DECODER)==0) men='2';												// Иначе выводим инструкцию
				else cout<<"LCoder <input_file> <output_file> <"<<CODER<<" (coder) or "<<DECODER<<" (decoder)> <KEY>\n";
				if(argc>4){
					KEY  =new char[strlen(argv[4]) + 1];													//4 элемент - ключ
					strcpy(KEY, argv[4]);
					if(men) print = false;																	//Если все элементы удалось собрать,
				}																							//то не будет вывода
			}
		}
	}
	
	if (print) cout<<"____________________LCoder v_0.7.1_______________________\n";							//Приветствие
	
    if(!men){																								//Если не было в консольном запросе 
    	men=menu();
    	if(men=='3')return 0;
	}
	if(men=='2') coder=false;																				//Устанавливаем переменную в режим декодирования
	
    while(1){																								//Открытие входного файла
        if(!name_in) {																						//Если имени не было в консоли
			cout<<"Enter a name input file: ";																//получим его здесь
			name_in = new char[NAME_SIZE];
			cin.getline(name_in, NAME_SIZE);
        	
			if(cin.fail()){																					//и проверим на ошибки
        		cout<<"\n_______________________invalide input1_________________\n\n";						
        		cin_clear();
				delete [] name_in;																			//и удаляем старое значение
				name_in = 0; 
        		continue;
			}
		}
        
        in.open(name_in, ios::in /*| ios::nocreat*/ |ios:: binary);											//Открытие файла
        
		if (in) break;																						//Если всё хорошо выходим
        else{
        	print = true;																					//Иначе печатаем сообщение 
        	cout<<"\n_______________________invalide name1__________________\n\n";
			delete [] name_in;																					//и удаляем старое значение
			name_in = 0;
		}  
    }
    if (print) cout<<"\n------------------ input file open! -------------------\n\n";	
    
    while(1){																								//Открытие выходного файла
        if(!name_out){																						//Если имени не было в консоли
			cout<<"Enter a name output file: ";
			name_out = new char[NAME_SIZE];
			cin.getline(name_out, NAME_SIZE);																//получим его здесь
			
			if(cin.fail()){																					//и проверим на ошибки
	    		cout<<"\n_______________________invalide input2_________________\n\n";
	    		cin_clear(); 
	    		delete [] name_out;
	    		name_out = 0;
	    		continue;
			} 
		}
			
		if (strcmp(name_out,STD_NAME)==0) {																//Проверяем имя на стандартное
    		if(men=='1'){																					//При кодировании
				delete name_out;
				name_out = new char[strlen(name_in) + strlen(STD_EXTEN) + 1];
				strcpy(name_out,name_in);																	//копируем входное имя
				strcat(name_out,STD_EXTEN);																	//и дописываем расширение
			}
    		else  																							//При декодировании
				if(strcmp( STD_EXTEN, name_in + (strlen(name_in) - strlen(STD_EXTEN)) )==0){				//проверяем последние символы строки
					delete [] name_out;
					name_out = new char[strlen(name_in) + 1];
					strcpy(name_out,name_in);																//если всё ок копируем в выходное имя начальное имя
					name_out[strlen(name_out)-strlen(STD_EXTEN)]='\0';										//и обрезаем по расширению
				}
    		else {																							//Если имя не стандартное
				print = true;																				// выводим сообщение и даем ещё попытку
	    		delete [] name_out;
	    		name_out = 0;
				cout<<"\n_______________________not standart name_______________\n\n";
	    		continue;
			}
		}  
		   
        out.open(name_out, ios::out | ios::trunc | ios:: binary);											//Открытие файла
        
		if (out) break;																						//Если всё хорошо выходим
        else{
        	print = true;																					//Иначе печатаем сообщение 
        	cout<<"\n_______________________invalide name2__________________\n\n";
			delete [] name_out;																				//и удаляем старое значение
			name_out = 0;
		}
    }
    if (print) cout<<"\n------------------ output file open! ------------------\n\n"; 
    
    if(KEY && !KEY_check(KEY,false)){
    	
    	if(strlen(KEY)==1 && KEY[0]>'0' && KEY[0]<='5') KEY = KEY_enter(KEY[0]);
    	else {
    		delete [] KEY;
    		KEY = 0;
		}
	}
																					//В этом режиме функция проверяет ключ на правильность
    if(!KEY){																								//Если ключа нет или он не правильный
    	print = true;																						//вывод сообщений
		if(men=='2'){																						//Если декодировать  
	    	KEY = KEY_enter('0');																			//то нужно знать код
	    }
	    else while(1){																						//Если кодировать
	            char ch;
	            cout<<"Enter level a coder( 1-5) or 0 for enter personal cod: ";          					//предлогаем уровень шифрования 
	            cin.get(ch);
	            cin_clear();
	            if(ch>='0' && ch<='5'){																		//проверяем на пределы
					KEY = KEY_enter(ch);																	//вводим код
					break;
				}
				cout<<"\n_______________________invalide number_________________\n\n";						//сообщаем о ошибке
	        }
	}
	
	time_t times=encryption(in, out, file_size, KEY, coder, print);											//Шифруем и получаем от функции время работы
	in.close();																								//Закрываем файлы
	out.close();
	if(print) report(men,name_in,name_out, KEY, times,file_size);											//Выводим информацию
    else if (men=='1') cout<<KEY<<'\n';
    
	delete [] KEY;
	delete [] name_in;
	delete [] name_out;
	return 0;
}

void cin_clear(){	cin.clear(); while(cin.get()!='\n'); }

																											//Шифруем символ 
char shifr(char ch, unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char p_z, bool coder=true){

	int gamma = (int)( p_z*(a + b*d  + d*a ) - a*b - c*d);													//Создаём гамму
	
	int sm = p_z*(11.0/255.0) + 5;																			//Задаем смещение и смещаем(рандомизируем) гамму
	gamma = (gamma>>sm) | (gamma<<sm);
	
	gamma = (char)(gamma ) + (char)(gamma>>24) - (char)(gamma>>16) + (char)(gamma>>8) ;						//Пакуем гамму в char попутно рандомизируем

	if(coder) ch+= gamma;																					//Накладываем или снимаем гамму
	else  	  ch-= gamma;

	return ch;
}

char menu(){																								//Меню приложения
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

char* KEY_enter (char ch){																					//Ввод ключа
	char *KEY = 0;
    if(ch=='0')	while(1){																					//Режим 0 - ручной ввод
			        cout<<"Enter KEY(max length "<<KEY_SIZE<<" ): ";
			        KEY = new char[KEY_SIZE + 1];
			        cin.getline(KEY, KEY_SIZE + 1);
			        if(cin.fail()){																			//Проверяем на ошибки
			        		cout<<"\n_______________________invalide KEY____________________\n\n";
			        		cin_clear(); 
			        		continue;
					}
					if(KEY_check(KEY))break;																//Проверяем правильность введения ключа
					delete [] KEY;				
				}
    else{																									//Режимы 1 2 3 4 5 - автоматическая генерация ключа
    	srand(time(NULL));
        int coder=(KEY_SIZE/5) * ( (int)ch -48);															//Вычисляем размер ключа
        
		KEY = new char[coder + 1];
        char *start_KEY = KEY;
        
		while(coder--)   *(KEY++)=(char)(rand()%94+32);														//Заполняем ключ не забывая о нуль-терминаторе
        *KEY='\0';
        
        KEY = start_KEY;																					//Востонавливаем ключ
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
