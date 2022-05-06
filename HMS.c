#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<time.h>
#include<dir.h>

#define user_size 100
#define patient_size 100
#define login_size 1000
#define userinfo_size 30
#define patientinfo_size 30
#define totalbed 20

#define STAFF "Database/staff.bin"
#define RECEPTION "Database/reception.bin"
#define PATIENT "Database/patient.bin"
#define BILLING "Database/patient_billing.bin"
#define LOGIN "Database/login.bin"
#define STAFF_BKP "Database/Backup/staff_bkp.bin"
#define RECEPTION_BKP "Database/Backup/reception_bkp.bin"
#define PATIENT_BKP "Database/Backup/patient_bkp.bin"
#define BILLING_BKP "Database/Backup/patient_billing_bkp.bin"
#define AUTOMATE "Database/automatic.bin"

#define ADMIN_NAME "ADMIN"
#define ADMIN_PASS "PASSWORD"


//**************** 1.Structures ************************************************

// 1.1 For storing Staff and Receptionist details (ADMIN).................
typedef struct usr {
	char name[userinfo_size];
	char address[userinfo_size];
	int age;
	long long int contact;
	char uname[userinfo_size];
	char password[userinfo_size];
	char removed[1];
	char access[1];

}usr;

usr staff[user_size], reception[user_size];


// 1.2 For storing Patients basic details (RECEPTIONIST).................

typedef struct patient{
	char name[patientinfo_size];
	char address[patientinfo_size];
	int age;
	char sex[1];
	long long int contact;
	char removed[1];

}pat;

pat patients[patient_size];



// 1.3 For storing Patients Billing details (STAFF).................
typedef struct billing{
	char name[patientinfo_size];
	int age;
	char sex[1];
	int bed;
	char service[patientinfo_size];
	char disease[patientinfo_size];
	long int charge;
	char discharge[1];
	char removed[1];

}bill;

bill billings[patient_size];


// 1.3 For storing login details (ADMIN).................

typedef struct login{
	int sn;
	char user[userinfo_size];
	char name[userinfo_size];
	char date[userinfo_size];
	char time[userinfo_size];
	

}log;

log loggins[login_size];


// 1.3 For storing AUTOMATIC details (ADMIN).................

typedef struct automatic{
	char userdb[30];
	usr userarr;
	int autobkp;
	int t[4];
	

}aut;
aut autarr;

//*********************************************************************************



//****************2. Function Declarations************************************************

// 2.1 Primary Functions Declatations...............
void admin_func();
void staff_func();
void reception_func();
void automatic_func();

// 2.2 Secondary Functions Declatations...............
const char* password();
const char* stringinp(int);
void stayin(void (*func)());
const char* stringedit(char []);
int choose_str(int );
int count_login();
int add_login(log ,int);
void add_recentlogin(char [],usr );
void edit_autobkp(int );
void reset_recentlogin();
void autobkp();
void backup_res_usr(usr [],char [],char [],char [],int );
void backup_res_patient(pat [],char [],char [],char [],int );
void backup_res_bill(bill [],char [],char [],char [],int );


// 2.3.1 Functions Declatations used by Admin...............
int count_user(usr [], char []); 
int add_user(usr [],int,char []);
usr read_user(usr [], char []);
int edit_user(usr [],char [],int);
int edit_user_disp(usr [], char [],int [],int);
int edit_user_edited(usr [], char [],int);
void display_user(usr [], char []);
int search_user_inp(usr [], char []);
int search_user_disp(usr [], char [],int [],int);
void display_login();
void backupandrestore();

// 2.3.3 Functions Declatations used by Receptionist and Staff...............
int count_patient(pat [],char []);
int add_patient(pat [],int,char []);
pat read_patient(pat [], char []);
int edit_patient_disp(pat [], char [],int [],int);
int edit_patient(pat [],char [],int);
int edit_patient_edited(pat [], char [],int);
int search_patient_inp(pat [],char [],int);
int search_patient_disp(pat [],char [], int [],int,int);
int search_patient_disp_staff(pat [],char [], int [],int,int);
void display_patient(pat [], char []);


// 2.3.2 Functions Declatations used by Staff.................
void display_billing_info(int ,int);
int edit_patient_bill(int);
int edit_patient_disp_bill(int [],int );
int edit_patient_edited_bill(int ,int );

//*********************************************************************************



//**************** 3. Primary Functions************************************************

//	3.1 Main Function................


int automatica=0;

int main(){	
	mkdir("Database");
	mkdir("Database\\Backup");
	system("COLOR F0");	
	if(automatica == 0){	
		automatic_func();
	}
	automatica=1;
	
	time_t t = time(NULL);
	struct tm*  ptm;
	int n,i,j,l,x=1;
	FILE *fp;
	
	log logtemp;
	char id[userinfo_size],pass[userinfo_size];
	
	wronguser:
	i=2;
	printf("\n\t----------------------------");
	printf("\n\tALLAY HOSPITAL PVT.LTD");
	printf("\n\t Durbarmargh,Kthmandu");
	printf("\n\t----------------------------");
	printf("\n\tChoose User:\n\t1 --> Administrator\n\t2 --> Staff\n\t3 --> Reception");
	printf("\n\t--------------------------\n");
	n = choose_str(1);
	switch(n){
		
		case 1:
	//	3.1.1 For Authentication of Admin........
			wrongadmin:
			printf("\n\tEnter ID For Admin:");
			strcpy(id,stringinp(userinfo_size));
			if(strcmp(id,"0")==0){
				system("cls");
				goto wronguser;
			}
			if((strcmp( password(),ADMIN_PASS) == 0) && (strcmp(id,ADMIN_NAME)==0)){
				
	    		ptm = localtime(&t);
				x = count_login();
				logtemp.sn = x;
				strcpy(logtemp.user,"admin");
				strcpy(logtemp.name,id);
	    		strftime(logtemp.time,userinfo_size, "%I:%M%p", ptm);
	    		strftime(logtemp.date,userinfo_size, "%x", ptm);
	    		add_login(logtemp,x);
				system("cls");
				reset_recentlogin();
				printf("\tLogged in to Admin as %s",id);
				admin_func();	
			}
			else{
				if(i>0){
				printf("\n\tWrong id or password.You have %d chance left\n",i);
				i--;
				goto wrongadmin;
				}
				else{
				printf("\n\tAll attempt failed!!.\n");
				l=59;
				while(l>=0){
					printf("\r\tWait until %dsec",l);
					l = l-1;
					sleep(1);
				}
				system("cls");
				goto wronguser;
				}
				
			}
			break;
				
		case 2:
			
//	3.1.2 For Authentication of Staff........
		
		fp = fopen(STAFF, "rb"); 
		fread(staff,sizeof(usr),user_size,fp);
		fclose(fp);
		wrongstaff:
		j=1;
		printf("\n\tEnter ID For Staff:");
		strcpy(id,stringinp(userinfo_size));
			if(strcmp(id,"0")==0){
				system("cls");
				goto wronguser;
			}
		strcpy(pass,password());
		while(staff[j].age != '\0') {
			if((strcmp(pass,staff[j].password) == 0) && strcmp(id,staff[j].uname) == 0 && staff[j].removed[0] != 'Y') {
	    		ptm = localtime(&t);
				x = count_login();
				logtemp.sn = x;
				strcpy(logtemp.user,"staff");
				strcpy(logtemp.name,id);
	    		strftime(logtemp.time,userinfo_size, "%I:%M%p", ptm);
	    		strftime(logtemp.date,userinfo_size, "%x", ptm);
				add_login(logtemp,x);
				
				add_recentlogin("Staff",staff[j]);
				system("cls");
				printf("\tLogged in to Staff as %s\n",staff[j].name);
				staff_func();	
				break;
			}
			j++;
		}
		
		if(i>0){
		printf("\n\tWrong id or password.You have %d chance left",i);
		i--;
		goto wrongstaff;
		}
		else{
			printf("\n\tAll attempt failed!!.\n");
			l=59;
			while(l>=0){
				printf("\r\tWait until %d s",l);
				l = l-1;
				sleep(1);
			}
			system("cls");
			goto wronguser;
			
		}
		break;
			
		case 3:
				
//	3.1.3 For Authentication of Reception........

		fp = fopen(RECEPTION, "rb"); 
		fread(reception,sizeof(usr),user_size,fp);
		fclose(fp);
		wrongreception:
		j=1;
		printf("\n\tEnter ID For Receptionits:");
		strcpy(id,stringinp(userinfo_size));
			if(strcmp(id,"0")==0){
				system("cls");
				goto wronguser;
			}
			
		strcpy(pass,password());
		while(reception[j].age != '\0') {
			if((strcmp(pass,reception[j].password) == 0) && strcmp(id,reception[j].uname) == 0 && reception[j].removed[0] != 'Y') {
			
	    		ptm = localtime(&t);
				x = count_login();
				logtemp.sn = x;
				strcpy(logtemp.user,"receipt");
				strcpy(logtemp.name,id);
	    		strftime(logtemp.time,userinfo_size, "%I:%M%p", ptm);
	    		strftime(logtemp.date,userinfo_size, "%x", ptm);
	    		
				add_recentlogin("Reception",reception[j]);
				system("cls");
				printf("\tLogged in to Reception as %s",reception[j].name);
				add_login(logtemp,x);
				reception_func();	
				break;
			}
			j++;
		}
		if(i>0){
		printf("\n\tWrong id or password.You have %d chance left\n",i);
		i--;
			goto wrongreception;
			}
			else{
				printf("\n\tAll attempt failed!!.\n");
				l=59;
				while(l>=0){
					printf("\r\tWait until %d s",l);
					l = l-1;
					sleep(1);
				}
				system("cls");
				goto wronguser;
				
			}
		break;
		
			
			
//	3.1.4 Wrong Choice.................
		default:
			system("cls");
			printf("\n\tWrong choice.Re-enter:");
			goto wronguser;
			
	}
	
}

//.....................................................




//	3.2.For  Administrator....................
	void admin_func(){
		automatica = 1;
		int n,x;
		char again[1];	
		printf("\n\t-----------------------------------------");
		printf("\n\tADMIN\n\t-----------------------------------------");
		printf("\n\tChoose what you want to do?\n\tSTAFF\t\t\tRECEPTION\n\t1 --> Add\t\t6 --> Add\n\t2 --> Remove\t\t7 --> Remove\n\t3 --> Edit\t\t8 --> Edit\n\t4 --> Search\t\t9 --> Search\n\t5 --> Display\t\t10 --> Display\n\n\t\t11 --> Logout as Admin\n\t\t12 -> Display Log info\n\t\t13 -> (Backup/Restore)");
		printf("\n\t-----------------------------------------\n");
		n = choose_str(2);
		switch(n){
			
			case 1:
				addagain1:
					x = count_user(staff,STAFF);
					add_user(staff,x,STAFF);
					printf("\n\tDo you want to Add More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto addagain1;
					}
					else{
						stayin(admin_func);
					};
					break;
			case 2:
				deleteagain1:
				edit_user(staff,STAFF,1);
				printf("\n\tDo you want to Delete More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto deleteagain1;
					}
					else{
						stayin(admin_func);
					};
				break;
			case 3:
				editagain1:
				edit_user(staff,STAFF,0);
				printf("\n\tDo you want to Edit More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto editagain1;
					}
					else{
						stayin(admin_func);
					};
				break;
			case 4:
				search_user_inp(staff,STAFF);
				break;
				
			case 5:
				display_user(staff,STAFF);
				stayin(admin_func);
				break;
				
				
				
			case 6:
				addagain2:
					x = count_user(reception,RECEPTION);
					add_user(reception,x,RECEPTION);
					printf("\n\tDo you want to Add More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto addagain2;
					}
					else{
						stayin(admin_func);
					};
					break;
			case 7:
				deleteagain2:
				edit_user(reception,RECEPTION,1);
				printf("\n\tDo you want to Delete More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto deleteagain2;
					}
					else{
						stayin(admin_func);
					};
			break;
			case 8:
				editagain2:
				edit_user(reception,RECEPTION,0);
				printf("\n\tDo you want to Edit More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto editagain2;
					}
					else{
						stayin(admin_func);
					};
				break;
			case 9:
				search_user_inp(reception,RECEPTION);
				break;
				
			case 10:
				display_user(reception,RECEPTION);
				stayin(admin_func);
				break;
			
			case 11:
				system("cls");
				printf("\n\tLogged out as Admin.");
				main();
				break;	
			case 12:
				display_login();
				stayin(admin_func);
				break;
			case 13:
				system("cls");
				backupandrestore();
				break;
			default:
				system("cls");
				printf("\n\tInvalid Choice.");
				admin_func();
		}
	}
	
//	3.3 For Staff (nurses and doctors who have access to the system).......
	void staff_func(){
		automatica = 1;
			int n,x;
		char again[1];	
		printf("\n\t-----------------------------------------");
		printf("\n\tStaff\n\t-----------------------------------------");
		printf("\n\tChoose what you want to do?\n\t1 --> Search Patient\n\t2 --> Edit Patients All Report\n\t3 --> Edit Patients Service\n\t4 --> Edit Patients Bed\n\t5 --> Edit Patients Disease\n\t6 --> Edit Patients Charge\n\t7 --> Edit Patients Discharge\n\t8 --> Logout as Staff");
		printf("\n\t-----------------------------------------\n");
		n = choose_str(2);
		switch(n){
			
					
			case 1:
				searchagain2:
				search_patient_inp(patients,PATIENT,1);
				printf("\n\tDo you want to Search More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto searchagain2;
					}
					else{
						stayin(staff_func);
					};
				break;
			case 2 ... 7:
				edit_patient_bill(n);
				break;
			case 8:
				system("cls");
				printf("\n\tLogged out as Staff.");
				main();
				break;	
			default:
				system("cls");
				printf("\n\tInvalid Choice.");
				staff_func();
		}
	}



//	3.4 For Receptionist.................
	void reception_func(){
		automatica = 1;
			int n,x;
		char again[1];	
		printf("\n\t-----------------------------------------");
		printf("\n\tReception\n\t-----------------------------------------");
		printf("\n\tChoose what you want to do?\n\t1 --> Add Patient\n\t2 --> Search Patient\n\t3 --> Edit Patient\n\t4 --> Display Patient\n\t5 --> Delete Patient\n\t6 --> Logout as Receptionist");
		printf("\n\t-----------------------------------------\n");
		n = choose_str(2);
		switch(n){
			
			case 1:
				addagain2:
					
				x = count_patient(patients,PATIENT);
				add_patient(patients,x,PATIENT);
					printf("\n\tDo you want to Add More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto addagain2;
					}
					else{
						stayin(reception_func);
					};
					break;
					
			case 2:
				searchagain2:
				search_patient_inp(patients,PATIENT,0);
				printf("\n\tDo you want to Search More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto searchagain2;
					}
					else{
						stayin(reception_func);
					};
				break;
				
			case 3:
				editagain2:
					
				edit_patient(patients,PATIENT,0);
				printf("\n\tDo you want to Edit More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto editagain2;
					}
					else{
						stayin(reception_func);
					};
				break;
				
			case 4:
				display_patient(patients,PATIENT);
				stayin(reception_func);
				break;
				
			case 5:
				printf("\n\t(Requires Admin)");
				deleteagain2:
				edit_patient(patients,PATIENT,1);
				printf("\n\tDo you want to Delete More?(Y/N)");
					strcpy(again,stringinp(1));
					if(again[0] == 'Y'){
						goto deleteagain2;
					}
					else{
					stayin(reception_func);
					};
				break;
		
			case 6:
				system("cls");
				printf("\n\tLogged out as Receptionist.");
				main();
				break;	
		
			default:
				system("cls");
				printf("\n\tInvalid Choice.");
				reception_func();
		}
		}



//	3.5 For Automatic.................
	void automatic_func(){
		
			FILE *fp;
			time_t t = time(NULL);
			struct tm*  ptm;
			ptm = localtime(&t);
			int x=1;
			log logtemp;
			fp = fopen(AUTOMATE, "rb");
			if(fp != NULL){	
				fread(&autarr,sizeof(aut),1,fp);
				fclose(fp);
				
				// For Automatic Backup...............................
				if(autarr.autobkp == 2){
					autobkp();
				}
				else if(autarr.autobkp == 3){
					if(autarr.t[1] >= ptm->tm_yday){
							if(autarr.t[0] < ptm->tm_hour){
								autobkp();
							}
					}
					else{
						autobkp();
					}
				}
				
				else if(autarr.autobkp == 4){
						if(autarr.t[3] >= ptm->tm_year){
							if(autarr.t[1] < ptm->tm_yday){
								autobkp();
							}
					}
					else{
						autobkp();	
					}
				}
				else if(autarr.autobkp == 5){
						if(autarr.t[3] >= ptm->tm_year){
							if(autarr.t[2] < (ptm->tm_yday/7)){
								autobkp();
							}
					}
					else{
						autobkp();
					}
				}
				
				// For Recently Logged in Automation...................
				if(strcmp(autarr.userdb,"0") != 0){
					printf("\n\tRecently logged in to %s as %s.",autarr.userdb,autarr.userarr.uname);
					if(strcmp(password(),autarr.userarr.password) == 0){
						if(strcmp(autarr.userdb,"Staff") == 0){
							x = count_login();
							logtemp.sn = x;
							strcpy(logtemp.user,"staff");
							strcpy(logtemp.name,autarr.userarr.uname);
				    		strftime(logtemp.time,userinfo_size, "%I:%M%p", ptm);
				    		strftime(logtemp.date,userinfo_size, "%x", ptm);
				    		add_login(logtemp,x);
				    		system("cls");
							printf("\tLogged in to Reception as %s",autarr.userarr.name);
							staff_func();
						}
						else if(strcmp(autarr.userdb,"Reception") == 0){
							
							x = count_login();
							logtemp.sn = x;
							strcpy(logtemp.user,"receipt");
							strcpy(logtemp.name,autarr.userarr.uname);
				    		strftime(logtemp.time,userinfo_size, "%I:%M%p", ptm);
				    		strftime(logtemp.date,userinfo_size, "%x", ptm);
				    		add_login(logtemp,x);
				    		system("cls");
							printf("\tLogged in to Reception as %s",autarr.userarr.name);
							reception_func();	
						}
						else;
					}	
					else{
				    	system("cls");
						printf("\tWrong Password for %s",autarr.userarr.name);
					}
				}

			}	
	}



//*******************************************************************************************
 


//	*************  4. Secondary Functions *******************************************************

		
//  4.1 For Password.............
	const char* password(){
		printf("\n\tEnter Password:");
		int i=0;
		char ch;
		char * pass = malloc(sizeof(char)*50);
		while(1){
			ch = getch();
			if(ch == 13 || ch == 9){
				if(i != 0){	
						pass[i] = '\0';
						break;
					}
			}
			else if(ch == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}
			else{
				pass[i++] = ch;
				printf("* \b");
			}
		}
		return strupr(pass);
	}
	
	
		
//  4.2 For String .............
	const char* stringinp(int x){
		int i=0;
		char ch;
		char * str = malloc(sizeof(char)*x);
		while(1){
			ch = getch();
			if(ch == 13 || ch == 9){
				if(i != 0){	
					str[i] = '\0';
					break;
				}
			}
			else if(ch == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}
			else{
				str[i++] = ch;
				printf("%c \b",toupper(ch));
			}
		}
		return strupr(str);
	}
	
	
//  4.3 For Edit User's Data Input String.............
const char* stringedit(char x[]){
		int i=0;
		char ch;
	 	char *str = malloc(sizeof(char)*userinfo_size);
		strcpy(str,x);
		while(str[i] != '\0'){
			printf("%c",str[i]);
			i++;
		}
		while(1){
			ch = getch();
			if(ch == 13 || ch == 9){
				if(i != 0){	
					str[i] = '\0';
					break;
				}
			}
			else if(ch == 8){
				if(i>0){
					i--;
					printf("\b \b");
				}
			}
			else{
				str[i] = ch;
				printf("%c",toupper(ch));
				i++;
			}	
		}	
		return strupr(str);
	
}
	

//  4.4 For Logging out or staying in.....................
	void stayin(void (*func)()){
	
		int i;
		wrongchoice1:
		printf("\n\t1 --> Back\n\t2 --> Logout");	
		i = choose_str(1);
		if(i==1){
			system("cls");
			func();	
		}
		else if(i==2){
			system("cls");
			printf("\tLogged out");
			main();
		}
		else {
		goto wrongchoice1;	
		}
}


// 4.5 For avoiding error while choosing...........

int choose_str(int x){
	printf("\t");
	return atoi(stringinp(x));
}


//  4.6 For Counting Numbers of Login...............
	int  count_login(){
		FILE *fp;
		fp = fopen(LOGIN, "rb");
		
		int j=1;	
		if(fp != NULL){
			fread(loggins,sizeof(log),user_size,fp);
			while(loggins[j].sn != '\0'){
				
					j = j+1;
			} 		
		}
		return j;
		fclose(fp);
	}
	
	
	
//  4.7 For Adding Login.............

	int add_login(log logtemp,int x){
		
			
			FILE *fp;
			fp = fopen(LOGIN, "wb");
			loggins[x] =  logtemp;
			fwrite(loggins,sizeof(log),user_size,fp);
			fclose(fp);
	}	

//  4.8 For Adding Recent Login.............
	void add_recentlogin(char userdb[],usr user){
			FILE *fp;
			fp = fopen(AUTOMATE, "rb");
			fread(&autarr,sizeof(aut),1,fp);
			fclose(fp);
			autarr.userarr = user;
			strcpy(autarr.userdb,userdb);
			fp = fopen(AUTOMATE, "wb");
			fwrite(&autarr,sizeof(aut),1,fp);
			fclose(fp);
			
	}
	
//  4.8 For Reset Recent Login.............
	void reset_recentlogin(char userdb[],usr user){
			FILE *fp;
			fp = fopen(AUTOMATE, "rb");
			fread(&autarr,sizeof(aut),1,fp);
			fclose(fp);
			strcpy(autarr.userdb,"0");
			fp = fopen(AUTOMATE, "wb");
			fwrite(&autarr,sizeof(aut),1,fp);
			fclose(fp);
			
	}
	
	

// 4.9 For Backup and Restorring Users Data.............
void backup_res_usr(usr user[],char userdb[],char destdb[],char ch[],int x){

		FILE *fp1,*fp2;
		fp1 = fopen(userdb, "rb");
		if(fp1 != NULL){
			fread(user,sizeof(usr),user_size,fp1);
			fp2 = fopen(destdb, "wb");
			fwrite(user,sizeof(usr),user_size,fp2);
			fclose(fp1);
			fclose(fp2);
			if(x ==1 ){
				printf("\n\tFile %s successfully to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}
		else{
			if(x ==1 ){
				printf("\n\tError to %s to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}

}

// 4.10 For Backup and Restorring Patients Data.............
void backup_res_patient(pat user[],char userdb[],char destdb[],char ch[],int x){
	
	FILE *fp1,*fp2;
		fp1 = fopen(userdb, "rb");
		if(fp1 != NULL){
			fread(user,sizeof(pat),patient_size,fp1);
			fp2 = fopen(destdb, "wb");
			fwrite(user,sizeof(pat),patient_size,fp2);
			fclose(fp1);
			fclose(fp2);
			if(x ==1 ){
				printf("\n\tFile %s successfully to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}
		else{
			if(x ==1 ){
				printf("\n\tError to %s to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}

}

// 4.11 For Backup and Restorring Billings Data.............
void backup_res_bill(bill user[],char userdb[],char destdb[],char ch[],int x){
	
	FILE *fp1,*fp2;
		fp1 = fopen(userdb, "rb");
		if(fp1 != NULL){
			fread(user,sizeof(bill),patient_size,fp1);
			fp2 = fopen(destdb, "wb");
			fwrite(user,sizeof(bill),patient_size,fp2);
			fclose(fp1);
			fclose(fp2);
			if(x ==1 ){
				printf("\n\tFile %s successfully to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}
		else{
			if(x ==1 ){
				printf("\n\tError to %s to %s",ch,destdb);
				stayin(backupandrestore);
			}
		}


}

// 4.12 For Backup and Restorring Data Automatically.............
	void edit_autobkp(int x){
		FILE *fp;
		time_t ptm = time(NULL);
		struct tm *t = localtime(&ptm);
		
			fp = fopen(AUTOMATE, "rb");
			fread(&autarr,sizeof(aut),1,fp);
			fclose(fp);
    		autarr.t[0] = t->tm_hour;
    		autarr.t[1] = t->tm_yday;
    		autarr.t[2] = t->tm_yday/7;
    		autarr.t[3] = t->tm_year;
			autarr.autobkp = x;
			fp = fopen(AUTOMATE, "wb");
			fwrite(&autarr,sizeof(aut),1,fp);
			fclose(fp);
	}

	
//  4.13 For Auto Backuoo.............
			
	void autobkp(){
					
			FILE *fp;
			time_t ptm = time(NULL);
			struct tm *t = localtime(&ptm);
		
			fp = fopen(AUTOMATE, "rb");
			fread(&autarr,sizeof(aut),1,fp);
			fclose(fp);
    		autarr.t[0] = t->tm_hour;
    		autarr.t[1] = t->tm_yday;
    		autarr.t[2] = t->tm_yday/7;
    		autarr.t[3] = t->tm_year;
			fp = fopen(AUTOMATE, "wb");
			fwrite(&autarr,sizeof(aut),1,fp);
			fclose(fp);
			
			backup_res_usr(staff,STAFF,STAFF_BKP,"Backed up",0);
			backup_res_usr(reception,RECEPTION,RECEPTION_BKP,"Backed up",0);
			backup_res_patient(patients,PATIENT,PATIENT_BKP,"Backed up",0);
			backup_res_bill(billings,BILLING,BILLING_BKP,"Backed up",0);
			printf("\n\tBacked up Successfully");
	}
	

//*******************************************************************************************





//	*************  5. Tertary Functions *******************************************************

//--------------- 5.1 For Administratiors......................................................

//  5.1.1 For Counting Numbers of users...............
	int  count_user(usr user[],char userdb[]){
		FILE *fp;
		fp = fopen(userdb, "rb");
		int j=1;	
		if(fp != NULL){
			fread(user,sizeof(usr),user_size,fp);
			while(user[j].age != '\0') 	j = j+1;	
		}
		fclose(fp);
		return j;
	}
	
	
	
//  5.1.2 For Adding User.............
	int add_user(usr user[],int x,char userdb[]){
			
			FILE *fp;
			fp = fopen(userdb, "wb");
			user[x] =  read_user(user,userdb);
			fwrite(user,sizeof(usr),user_size,fp);
			fclose(fp);
	}	
	
	
	
//  5.1.3 For Reading User's Data.............
	usr read_user(usr user1[],char userdb[]){
			usr user;
			int i;
			char c[25];
			FILE *fp;
			fp = fopen(userdb, "rb");
			fread(user1,sizeof(usr),user_size,fp);
			//  For Full Name.........................
			printf("\n\tEnter Full Name:");
			
			strcpy(user.name,stringinp(sizeof(user.name)));
			if(strcmp(user.name,"0")==0){
				system("cls");
				admin_func();
			}
			
			//  For Ages.........................		
			ages:
			printf("\n\tEnter Age:");
			user.age = choose_str(2);
			if(user.age == 0){
				system("cls");
				admin_func();
			}
			else if(user.age>100 || user.age<0){
				printf("Invalid Age!");
				goto ages;
			}

			
			//  For Address.........................	
			printf("\n\tEnter Address:");
			strcpy(user.address,stringinp(sizeof(user.address)));
			if(strcmp(user.address,"0")==0){
				system("cls");
				admin_func();
			}
			
			//  For Contact.........................
			contacts:	
			printf("\n\tEnter Contact:");
			user.contact = choose_str(10);
			if(user.contact == 0){
				system("cls");
				admin_func();
				
				}
			
			else if(user.contact>9999999999 || user.contact<0){
				printf("Invalid Contact!");
				goto contacts;
			}
			//  For Username.........................	
			usernames1:
			printf("\n\tEnter Username(no spaces.):");
			strcpy(c,stringinp(sizeof(user.uname)));
			if(strcmp(user.uname,"0")==0){
				system("cls");
				admin_func();
			}
			i=0;
			while(c[i] != '\0'){
				if(c[i] == 32){
					printf("\n\tInvalid Username!!");
					goto usernames1;
				}
				i++;
			}
			int j=1;	
			while(user1[j].age != '\0'){
				if(strcmp(user1[j].uname,c) == 0 && user1[j].removed[0] == 'n'){
					printf("\n\tUser name  already exits.");
					goto usernames1;
				};
				j = j+1;	
			} 	
			fclose(fp);
			strcpy(user.uname,c);
			
			//  For Password.........................	
			printf("\n\tEnter Password:");
			strcpy(user.password,stringinp(sizeof(user.password)));
			if(strcmp(user.password,"0")==0){
				system("cls");
				admin_func();
			}
			user.removed[0]='N';
			user.access[0]='Y';
			return user;
	}
	

	
//  5.1.4 For Editing and Deleting  User's Data.............
	int edit_user(usr user[],char userdb[],int i){
		
		FILE *fp;
		fp = fopen(userdb, "rb"); 
		int flag = 1,j=1,x[user_size];
			char ch[userinfo_size],c[1];
			if(fp != NULL){
				
				printf("\n\tEnter Users Username:");
				strcpy(ch,stringinp(userinfo_size));
				fread(user,sizeof(usr),user_size,fp);
				
				while(user[j].age != '\0') {
					if(strcmp(user[j].uname,ch) == 0 && user[j].removed[0] != 'Y'){
						x[flag] = j;
						flag++;	
					}
					j = j+1;
				}
			}
			
			else{
				printf("\n\tNo User found!");
				stayin(admin_func);
			}
			
		if(flag == 1){
			printf("\n\tNo user Found.");
			stayin(admin_func);
		}
		else{
			
			j=edit_user_disp(user,userdb,x,flag-1);
			
			
			if(i==0){
				edit_user_edited(user,userdb,j);
			}
			else{
				
			printf("\n\tEnter Admin Id to remove:");
			strcpy(ch,stringinp(userinfo_size));
			if((strcmp( password(),ADMIN_PASS) == 0) && (strcmp(ch,ADMIN_NAME)==0)){
					user[j].removed[0],'Y';
					user[j].access[0],'N';
					fclose(fp); 
					fp = fopen(userdb,"wb");
					fwrite(user,sizeof(usr),user_size,fp);
					fclose(fp);
					printf("\n\t%s's data Removed Successfully. %c",user[j].name,c[0]);
				}
				else{
					printf("\n\t%s's data  Not Removed.",user[j].name);
				}
				
			}

			
		}
		
	}
	
	
	

// 5.1.5 For Display Edited User's Data.............
int edit_user_disp(usr user[],char userdb[], int x[],int count){
		system("cls");
		int i,choose;
				FILE *fp;
				fp = fopen(userdb, "rb");
					fread(user,sizeof(usr),user_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED USERS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
					printf("\n\tAccess Removed Age\tUname\tPassword\tContact\tFull Name");	
					for(i=1; i<=count; i++){
						printf("\n\t%c\t%c\t%d\t%s\t%s\t\t%lld\t%s",user[x[i]].access[0],user[x[i]].removed[0],user[x[i]].age,user[x[i]].uname,user[x[i]].password,user[x[i]].contact,user[x[i]].name);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");
				printf("\n\tChoose:\n\t0 --> Back");
				for(i=1; i<=count; i++){
					printf("\n\t%d --> %s(%s)",i,user[x[i]].name,user[x[i]].uname);
				}
				printf("\n\t");
				wrongsearchedit1:
				choose = choose_str(2);
				if(choose == 0){
					system("cls");
					admin_func();
				} 
				else if(choose>=1 && choose<=count){
				return x[choose];
				}
				else{
					printf("\n\tInvalid Choice.");
					goto wrongsearchedit1;
				}
			fclose(fp);		
}



	

// 5.1.6 For Edit User's Data.............

	int edit_user_edited(usr user[],char userdb[],int j){
		usr useredit;
		FILE *fp;
		fp = fopen(userdb, "rb");
			
			printf("\n\tEdit Name:");
			strcpy(useredit.name,stringedit(user[j].name));
			if(strcmp(useredit.name,"0")==0){
				system("cls");
				admin_func();
			}
			printf("\n\tEdit Address:");
			strcpy(useredit.address,stringedit(user[j].address));
			if(strcmp(useredit.address,"0")==0){
				system("cls");
				admin_func();
			}
			userage1:
			printf("\n\tEdit Age(%d):",user[j].age);
			useredit.age = choose_str(2);
			if(useredit.age == 0){
				system("cls");
				admin_func();
			}
			if(useredit.age < 0 || useredit.age>100){
					printf("\n\tInvalid Age!!");
					goto userage1;
				}
			
			
			usercontact1:
			printf("\n\tEdit Contact(%d):",user[j].contact);
			useredit.contact = choose_str(10);
			if(useredit.contact == 0){
				system("cls");
				admin_func();
			}
			
			if(useredit.age < 0 || useredit.age>9999999999){
					printf("\n\tInvalid Contace!!");
					goto usercontact1;
				}
			
			
			usernames1:
			printf("\n\tEdit Username:");
			strcpy(useredit.uname,stringedit(user[j].uname));
			
			if(strcmp(useredit.uname,"0")==0){
				system("cls");
				admin_func();
			}
			int i=0;
			while(useredit.uname[i] != '\0'){
				if(useredit.uname[i] == 32){
					printf("\n\tInvalid Username!!");
					goto usernames1;
				}
				i++;
			}
			int k=1;	
			while(user[k].age != '\0'){
				if(strcmp(user[j].uname,useredit.uname) != 0){
					if(strcmp(user[k].uname,useredit.uname) == 0 && user[k].removed[0] != 'y'){
						printf("\n\tUser name  already exits.");
						goto usernames1;
					}
			}
				k = k+1;	
			} 	
			
			
			printf("\n\tEdit Password:");
			strcpy(useredit.password,stringedit(user[j].password));
			
			if(strcmp(useredit.password,"0")==0){
				system("cls");
				admin_func();
			}
			
			
			printf("\n\tEdit Access(y/n):");
			wrongaccessedit1:
			strcpy(useredit.access,stringinp(1));
			if(useredit.access[0] != 'Y' && useredit.access[0] !='N'){
				
				printf("\n\tInvalid Choice.");
				goto wrongaccessedit1;
			}
			
		printf("%s",useredit.name);	
		fclose(fp);
		
		
		
		
		fp = fopen(userdb,"wb");
		strcpy(user[j].address,useredit.address);
		
			
		strcpy(user[j].name,useredit.name);
		strcpy(user[j].uname,useredit.uname);
		strcpy(user[j].password,useredit.password);
		user[j].age = useredit.age;
		user[j].contact = useredit.contact;
		strcpy(	user[j].access,useredit.access);
		fwrite(user,sizeof(usr),user_size,fp);
		fclose(fp);
		printf("\n\t%s's data Edited Successfully.",user[j].name);
		}
		
	

// 5.1.7 For Input Searching  Data.............
int search_user_inp(usr user[],char userdb[]){
	
	char ch[userinfo_size];
	long long int pnumber;
	int j,count,choose,x[user_size];
	
	printf("\n\tSearch with?\n\t1 --> Username\n\t2 --> Full Name\n\t3 --> Contact\n\t4 --> Address\n\t5 --> Go Back");
	
	wrongsearchinp:
	choose = choose_str(1);
	if(choose>5 || choose<1){
		printf("\n\tInvalid Choice");
		goto wrongsearchinp;
	}
	j=1;
	count=0;
	FILE *fp;
	fp = fopen(userdb, "rb"); 
	if(fp != NULL){
		fread(user,sizeof(usr),user_size,fp);
			
		}
		else{
			printf("\n\tFile not found!");
		}
	
	fclose(fp);
		switch(choose){
			case 1:
				printf("\n\tEnter UserName:");
				strcpy(ch,stringinp(userinfo_size));
				while(user[j].age != '\0') {
					if(strcmp(user[j].uname,ch) == 0 && user[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
						
					}
					j = j+1;
				}
				break;
			case 2:
				printf("\n\tEnter Full Name:");
				strcpy(ch,stringinp(userinfo_size));
				while(user[j].age != '\0') {
					if(strcmp(user[j].name,ch) == 0 && user[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
						
					}
					j = j+1;
				}
				break;
			case 3:
				printf("\n\tEnter Contact:");
				scanf("%lld",&pnumber);
				while(user[j].age != '\0') {
					if(user[j].contact == pnumber && user[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
						
					}
					j = j+1;
				}
				break;
			case 4:
				printf("\n\tEnter Address:");
				strcpy(ch,stringinp(userinfo_size));
				while(user[j].age != '\0') {
					if(strcmp(user[j].address,ch) == 0 && user[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
					}
					j = j+1;
				}
				break;
			case 5:
				system("cls");
				admin_func();
				break;
		}
		if(count!=0) search_user_disp(user,userdb,x,count);
		else{
			printf("\n\tUser not found.");
			goto wrongsearchinp;
		}
		return 0;
}

			
// 5.1.8 For Display Searched User's Data.............
int search_user_disp(usr user[],char userdb[], int x[],int count){
		system("cls");
		int i,choose;
				FILE *fp;
				fp = fopen(userdb, "rb");
					fread(user,sizeof(usr),user_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED USERS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
					printf("\n\tAccess Removed Age\tUname\tPassword\tContact\tFull Name");	
					for(i=1; i<=count; i++){
						printf("\n\t%c\t%c\t%d\t%s\t%s\t\t%lld\t%s",user[x[i]].access[0],user[x[i]].removed[0],user[x[i]].age,user[x[i]].uname,user[x[i]].password,user[x[i]].contact,user[x[i]].name);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");	
				stayin(admin_func);
}


// 5.1.9 For Display User's Data.............
void display_user(usr user[],char userdb[]){
	system("cls");
	FILE *fp;
		fp = fopen(userdb, "rb");
		if(fp != NULL){
		fread(user,sizeof(usr),user_size,fp);
		}
		else{
			printf("\n\tNot found!!!!");
		}
		fclose(fp);
		int j=1;
		printf("\n\t---------------------------------------------------------------------------------------------------------\n");
		printf("\tUSERS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
		printf("\n\tAccess Removed Age\tUname\tPassword\tContact\tFull Name");		
		while(user[j].age != '\0') {
			
			if(user[j].removed[0] != 'Y'){
						printf("\n\t%c\t%c\t%d\t%s\t%s\t\t%lld\t%s",user[j].access[0],user[j].removed[0],user[j].age,user[j].uname,user[j].password,user[j].contact,user[j].name);
						
			}
			
			j = j+1;
		}
		
		printf("\n\t---------------------------------------------------------------------------------------------------------");
		
}




// 5.1.9 For Display Login Data.............
	void display_login(){
		system("cls");
		FILE *fp;
		fp = fopen(LOGIN, "rb");
		if(fp != NULL){
		fread(loggins,sizeof(log),user_size,fp);
		}
		else{
			printf("\n\tNot found!!!!");
		}
		fclose(fp);
		int j=1,sn;
		printf("\n\t---------------------------------------------------------------------");
		printf("\n\tLOGIN DETAILS\n\t---------------------------------------------------------------------");
		printf("\n\tS.N\tDate\t\tTime\t\tUser\t\tUserName");	
		
		while(loggins[j].sn != '\0'){
			printf("\n\t%d\t%s\t%s\t\t%s\t\t%s",j,loggins[j].date,loggins[j].time,loggins[j].user,loggins[j].name);
			j++;
		}
	
		printf("\n\t-------------------------------------------------------------------");
		
}

// 5.1.10 For Backup and Restorring Data.............
void backupandrestore(){
		int n,m;
		char again,x[1];	
		printf("\n\t-----------------------------------------");
		printf("\n\tBACKUP AND RESTORE\n\t-----------------------------------------");
		printf("\n\tChoose what you want to do?\n\tBACKUP\t\t\tRESTORE\n\t1 --> Staff\t\t5 --> Staff\n\t2 --> Reception\t\t6 --> Reception\n\t3 --> Patient\t\t7 --> Patient\n\t4 --> Billing\t\t8 --> Billing\n\t\t9 --> Auto Backup\n\t\t10 --> Go Back");
		printf("\n\t-----------------------------------------\n");
		wrongbackup:
		n = choose_str(2);
		if(n>=1 && n<9){
			printf("\n\tAre you sure you want to Backup/Restore?(Y/N)");
			strcpy(x,stringinp(1));
			if(x[0]=='y' || x[0]=='Y'){
				
				switch(n){
					case 1:
						backup_res_usr(staff,STAFF,STAFF_BKP,"Backed up",1);
						break;
					case 2:
						backup_res_usr(reception,RECEPTION,RECEPTION_BKP,"Backed up",1);
						break;
					case 3:
						backup_res_patient(patients,PATIENT,PATIENT_BKP,"Backed up",1);
						break;
					case 4:
						backup_res_bill(billings,BILLING,BILLING_BKP,"Backed up",1);
						break;
					case 5:
						backup_res_usr(staff,STAFF_BKP,STAFF,"Restored",1);
						break;
					case 6:
						backup_res_usr(reception,RECEPTION_BKP,RECEPTION,"Restored",1);
						break;
					case 7:
						backup_res_patient(patients,PATIENT_BKP,PATIENT,"Restored",1);
						break;
					case 8:
						backup_res_bill(billings,BILLING_BKP,BILLING,"Restored",1);
						break;
	
				}
			}
			else{
				system("cls");
				backupandrestore();
			}
				
		}
		else if(n == 9){
			
			printf("\n\tAuto Backup Setting:\n\t1 --> Turn Off\n\t2 --> Instantly\n\t3 --> Hourly\n\t4 --> Daily\n\t5 --> Weekly");
			wrongautobackup:
			m = choose_str(2);
			if(m < 1 || m > 5 ){
				printf("\n\tInvalid Choice");
				goto wrongautobackup;
			}
			edit_autobkp(m);
			system("cls");
			printf("\n\tAuto Backup setting saved successfully!");
			backupandrestore();
			
		}
		else if(n == 10){
	
			system("cls");
			admin_func();
		}
		else{
			printf("\n\tInvalid Choice.");
			goto wrongbackup;
		}
	
}

//----------------------------------------------------------------------------------------------












//--------------- 5.2 For Reception......................................................

//  5.2.1 For Counting Numbers of Patients...............
	int  count_patient(pat patient[],char patientdb[]){
		FILE *fp;
		fp = fopen(patientdb, "rb");
		int j=1;	
		if(fp != NULL){
			fread(patient,sizeof(pat),patient_size,fp);
			while(patient[j].age != '\0') 	j = j+1;	
		}
		fclose(fp);
		return j;
	}
	
	
	
//  5.2.2 For Adding Patients.............
	int add_patient(pat patients[],int x,char patientdb[]){
			FILE *fp;
			fp = fopen(patientdb, "wb");
			patients[x] =  read_patient(patients,patientdb);
			fwrite(patients,sizeof(pat),patient_size,fp);
			fclose(fp);
			fp = fopen(BILLING, "wb+");
			fread(billings,sizeof(bill),patient_size,fp);
			strcpy(billings[x].name,patients[x].name);
			billings[x].age =  patients[x].age;
			billings[x].sex[0] =  patients[x].sex[0];
			billings[x].bed = 0;
			strcpy(billings[x].service,"OPD");
			strcpy(billings[x].disease,"NYD");
			billings[x].charge = 0;
			billings[x].discharge[0] = 'N';
			billings[x].removed[0] = 'N';
			fwrite(billings,sizeof(bill),patient_size,fp);
			fclose(fp);
	}	
	
	
	
//  5.2.3 For Reading Patient's Data.............
	pat read_patient(pat patients1[],char patientdb[]){
			pat patients;
			int i;
			char c[25];
			FILE *fp;
			fp = fopen(patientdb, "rb");
			fread(patients1,sizeof(pat),patient_size,fp);
			
			//  For First Name.........................
			
			printf("\n\tEnter Patients Full Name:");
			strcpy(patients.name,stringinp(sizeof(patients.name)));
			if(strcmp(patients.name,"0")==0){
				system("cls");
				reception_func();
			}
			
			//  For Ages.........................		
			ages2:
			printf("\n\tEnter Age:");
			patients.age = choose_str(2);
			if(patients.age == 0){
					system("cls");
				reception_func();
				}
			if(patients.age <0){
				printf("Invalid Age");
				goto ages2;
			}
			//  For Address.........................	
			printf("\n\tEnter Address:");
			strcpy(patients.address,stringinp(sizeof(patients.address)));
			if(strcmp(patients.address,"0")==0){
				system("cls");
				reception_func();
			}
			
			//  For Contact.........................
			contacts2:	
			printf("\n\tEnter Contact:");
			patients.contact = choose_str(10);
			
			if(patients.contact == 0){
					system("cls");
					reception_func();
				}
				if(patients.contact<0 || patients.contact>9999999999){
					printf("Invalid Contact");
					goto contacts2;
				}
			
			//  For Sex.........................
			sex2:
			printf("\n\tEnter Sex(M/F):");
			strcpy(	patients.sex,stringinp(1));
			
				if((patients.sex[0] !='M') && (patients.sex[0] != 'F')){
					printf("\n\tInvalid Sex!!");
					goto sex2;
				}

			
			patients.removed[0]='N';
			return patients;
	}
	
	
		
//  5.2.4 For Editing and Deleting  Patients's Data.............
	int edit_patient(pat patients[],char patientdb[],int i){
		
		FILE *fp;
		fp = fopen(patientdb, "rb"); 
		int flag = 1,j=1,x[user_size];
			char ch[patientinfo_size],c[1];
			if(fp != NULL){
				
				printf("\n\tEnter Patients Full Name:");
				strcpy(ch,stringinp(patientinfo_size));
				fread(patients,sizeof(pat),patient_size,fp);
				
				while(patients[j].age != '\0') {
					if(strcmp(patients[j].name,ch) == 0 && patients[j].removed[0] != 'Y'){
						x[flag] = j;
						flag++;	
					}
					j = j+1;
				}
			}
			
			else{
				printf("\n\tNo PATIENT found!");
				stayin(reception_func);
			}
			
		if(flag == 1){
			printf("\n\tNo PATIENT Found!");
				stayin(reception_func);
		}
		else{
			
			j = edit_patient_disp(patients,patientdb,x,flag-1);
			if(i==0){
				edit_patient_edited(patients,patientdb,j);
			}
			else{
				
			printf("\n\tEnter Admin Id to remove:");
			strcpy(ch,stringinp(userinfo_size));
			if((strcmp( password(),ADMIN_PASS) == 0) && (strcmp(ch,ADMIN_NAME)==0)){
					patients[j].removed[0]='Y';
					fclose(fp); 
					fp = fopen(patientdb,"wb");
					fwrite(patients,sizeof(pat),patient_size,fp);
					fclose(fp);
					
					fp = fopen(BILLING,"wb+");
					fread(billings,sizeof(bill),patient_size,fp);
					billings[j].removed[0] = 'Y';
					fwrite(patients,sizeof(pat),patient_size,fp);
					fclose(fp);
					printf("\n\t%s's data Removed Successfully. %c",patients[j].name,c[0]);
				}
				else{
					printf("\n\t%s's data  Not Removed.",patients[j].name);
				}
				
			}

			
		}
		
	}
	
	
	

// 5.2.5 For Display Edited Patient's Data.............
int edit_patient_disp(pat patients[],char patientdb[], int x[],int count){
		system("cls");
		int i,choose;
				FILE *fp;
				fp = fopen(patientdb, "rb");
					fread(patients,sizeof(pat),patient_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED PATIENTS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
					printf("\n\tName\tAddress\tAge\tSex\tContact");	
					for(i=1; i<=count; i++){
						printf("\n\t%s\t%d\t%d\t%c\t%lld",patients[x[i]].name,patients[x[i]].address,patients[x[i]].age,patients[x[i]].sex[0],patients[x[i]].contact);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");
				printf("\n\tChoose:\n\t0 --> Back");
				for(i=1; i<=count; i++){
					printf("\n\t%d --> %s",i,patients[x[i]].name);
				}
				printf("\n\t");
				wrongsearchedit2:
				choose = choose_str(2);
				if(choose == 0){
					system("cls");
					reception_func();
				} 
				else if(choose>=1 && choose<=count){
				return x[choose];
				}
				else{
					printf("\n\tInvalid Choice.");
					goto wrongsearchedit2;
				}
			fclose(fp);		
}


// 5.2.6 For Editing Patients Data..............
int edit_patient_edited(pat patients[],char patientdb[],int j){
		pat patientedit;
		FILE *fp;
		fp = fopen(patientdb, "rb");
			
			printf("\n\tEdit Name:");
			strcpy(patientedit.name,stringedit(patients[j].name));	
			
			if(strcmp(patientedit.name,"0")==0){
				system("cls");
				reception_func();
			}
			printf("\n\tEdit Address:");
			strcpy(patientedit.address,stringedit(patients[j].address));
			
			if(strcmp(patientedit.address,"0")==0){
				system("cls");
				reception_func();
			}
			
			patientage1:
			printf("\n\tEdit Age(%d):",patients[j].age);
			patientedit.age = choose_str(2);
			if(patientedit.age < 0){
					printf("\n\tInvalid Age!!");
					goto patientage1;
				}
				
				
			if(patientedit.age ==0){
				system("cls");
				reception_func();
			}
			
			patientcontact1:
			printf("\n\tEdit Contact(%d):",patients[j].contact);
			patientedit.contact = choose_str(10);
			if(patientedit.contact < 0 || patientedit.contact > 9999999999){
					printf("\n\tInvalid Contact!!");
					goto patientcontact1;
			}
			
			if(patientedit.contact ==0){
				system("cls");
				reception_func();
			}
			printf("\n\tEdit Sex(M/F):");
			wrongsexedit1:
			strcpy(patientedit.sex,stringinp(1));
			if((patientedit.sex[0] !='M') && (patientedit.sex[0] != 'F')){
					printf("\n\tInvalid Sex!!");
					goto wrongsexedit1;
				}

			
		fclose(fp);
		fp = fopen(patientdb,"wb");
		strcpy(patients[j].name,patientedit.name);
		strcpy(patients[j].address,patientedit.address);
		patients[j].age = patientedit.age;
		patients[j].contact = patientedit.contact;
		strcpy(patients[j].sex,patientedit.sex);
		fwrite(patients,sizeof(pat),patient_size,fp);
		fclose(fp);
			fp = fopen(BILLING, "rb+");
			fread(billings,sizeof(bill),patient_size,fp);
			strcpy(billings[j].name,patientedit.name);
			billings[j].age =  patientedit.age;
			billings[j].sex[0] =  patientedit.sex[0];
			fwrite(billings,sizeof(bill),patient_size,fp);
			fclose(fp);
		printf("\n\t%s's data Edited Successfully.",patients[j].name);
		}
		
	

// 5.2.7 For Input Searching Patients Data.............
int search_patient_inp(pat patients[],char patientdb[],int l){
	
	char ch[patientinfo_size],cha[patientinfo_size],cha1[patientinfo_size];
	long long int pnumber;
	int j,count,choose,x[patient_size],i,k,flag;
	char *ptr, *lname,*fname;
	
	
	printf("\n\tSearch with?\n\t1 -->Name\n\t2 --> Contact\n\t3 --> Address\n\t4 --> Go Back");
	
	wrongsearchinp2:
	choose = choose_str(1);
	if(choose>5 || choose<1){
		printf("\n\tInvalid Choice");
		goto wrongsearchinp2;
	}
	j=1;
	count=0;
	FILE *fp;
	fp = fopen(patientdb, "rb"); 
	if(fp != NULL){
		fread(patients,sizeof(pat),patient_size,fp);
			
		}
		else{
			printf("\n\tFile not found!");
		}
	
	fclose(fp);
		switch(choose){
			case 1:
				printf("\n\tEnter Full Name:");
				strcpy(cha1,stringinp(patientinfo_size));
					strcpy(ch,cha1);
						ptr = strtok(ch, " ");
						fname = ptr;
						while(ptr != NULL)
						{
							lname= ptr;
							ptr = strtok(NULL, " ");
						}
						
						while(patients[j].age != '\0') {
							if(strcmp(patients[j].name,cha1) == 0 && patients[j].removed[0] != 'Y'){
								count++;
								x[count] = j;
							}
							j = j+1;
						}
						
							
						j=1;
						while(patients[j].age != '\0') {
							i=0;
							while(patients[j].name[i+strlen(fname)-1] != '\0'){
								strncpy(cha,&patients[j].name[i],strlen(fname));
								if((strcmp(cha,fname) == 0) && patients[j].removed[0] != 'Y' ){
									
										flag=0;
										for(k=0;k<=count;k++){
											if(x[k]==j){
												flag=1;
												break;
										}
									}	
										if(flag==0){
											count++;
											x[count] = j; 
										}
								}
								i++;
							}
							j++;	
						}
						
						
						
						j=1;
						while(patients[j].age != '\0') {
							i=0;
							while(patients[j].name[i+strlen(lname)-1] != '\0'){
								strncpy(cha,&patients[j].name[i],strlen(lname));
								if((strcmp(cha,lname) == 0) && patients[j].removed[0] != 'Y' ){
										
										flag=0;
										for(k=0;k<=count;k++){
											if(x[k]==j){
												flag=1;
												break;
										}
									}
										if(flag==0){
											count++;
											x[count] = j; 
										}
								}
								i++;
							}
							j++;	
						}
				break;
				
			case 2:
				printf("\n\tEnter Contact:");
				scanf("%lld",&pnumber);
				while(patients[j].age != '\0') {
					if(patients[j].contact == pnumber && patients[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
						
					}
					j = j+1;
				}
				break;
			case 3:
				printf("\n\tEnter Address:");
				strcpy(ch,stringinp(userinfo_size));
				while(patients[j].age != '\0') {
					if(strcmp(patients[j].address,ch) == 0 && patients[j].removed[0] != 'Y'){
						count++;
						x[count] = j;
					}
					j = j+1;
				}
				break;
			case 4:
				system("cls");
			if(l==0){
				reception_func();
			}
			else{
				staff_func();
			}
				break;
		}
		if(count!=0) {
			if(l==0){
				search_patient_disp(patients,patientdb,x,count,l);	
			}	
			else{
				search_patient_disp_staff(patients,patientdb,x,count,l);
			}
		}
		else{
			printf("\n\tUser not found.");
			goto wrongsearchinp2;
		}
		return 0;
}

			
// 5.2.8 For Display Searched Patients's Data.............
int search_patient_disp(pat patients[],char patientdb[], int x[],int count,int l){
		system("cls");
		int j,choose;
				FILE *fp;
				fp = fopen(patientdb, "rb");
					fread(patients,sizeof(pat),patient_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED USERS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
						printf("\n\tFull Name\tAddress\tAge\tSex\tContact");		
					for(j=1; j<=count; j++){
						printf("\n\t%s\t%s\t%d\t%c\t%lld",patients[x[j]].name,patients[x[j]].address,patients[x[j]].age,patients[x[j]].sex[0],patients[x[j]].contact);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");
					printf("\n\tChoose:\n\t0 --> Back");
				for(j=1; j<=count; j++){
					printf("\n\t%d --> %s's Billing Info",j,patients[x[j]].name);
				}
				printf("\n\t");
				wrongsearchedit3:
				choose = choose_str(2);
				if(choose == 0){
					system("cls");
					reception_func();
				} 
				else if(choose>=1 && choose<=count){
					display_billing_info(x[choose],l);
				}
				else{
					printf("\n\tInvalid Choice.");
					goto wrongsearchedit3;
				}
			fclose(fp);
				
		}


			
// 5.2.9 For Display Searched Patients's Data Staff Viewpoint.............
int search_patient_disp_staff(pat patients[],char patientdb[], int x[],int count,int l){
		system("cls");
		int j,choose;
				FILE *fp;
				fp = fopen(patientdb, "rb");
					fread(patients,sizeof(pat),patient_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED PATIENTS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
						printf("\n\tFull Name\tAge\tSex");		
					for(j=1; j<=count; j++){
						printf("\n\t%s\t%d\t%c",patients[x[j]].name,patients[x[j]].age,patients[x[j]].sex[0]);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");
					printf("\n\tChoose:\n\t0 --> Back");
				for(j=1; j<=count; j++){
					printf("\n\t%d --> %s's Billing Info",j,patients[x[j]].name);
				}
				printf("\n\t");
				wrongsearchedit4:
				choose = choose_str(2);
				if(choose == 0){
					system("cls");
					staff_func();
				} 
				else if(choose>=1 && choose<=count){
					display_billing_info(x[choose],l);
				}
				else{
					printf("\n\tInvalid Choice.");
					goto wrongsearchedit4;
				}
			fclose(fp);
				
		}

// 5.2.10 For Display Patients's Data Full.............
void display_patient(pat patients[],char patientdb[]){
	system("cls");
	FILE *fp;
		fp = fopen(patientdb, "rb");
		if(fp != NULL){
		fread(patients,sizeof(pat),patient_size,fp);
		}
		else{
			printf("\n\tNo PATIENT found!!!!");
		}
		fclose(fp);
		int j=1;
		printf("\n\t---------------------------------------------------------------------------------------------------------\n");
		printf("\tPATIENTS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
		printf("\n\tFull Name\tAddress\tAge\tSex\tContact");		
		while(patients[j].age != '\0') {
			
			if(patients[j].removed[0] != 'Y'){
						printf("\n\t%s\t%s\t%d\t%c\t%lld",patients[j].name,patients[j].address,patients[j].age,patients[j].sex[0],patients[j].contact);
						
			}
			
			j = j+1;
		}
		
		printf("\n\t---------------------------------------------------------------------------------------------------------");
		
}

//----------------------------------------------------------------------------------------------












//--------------- 5.2 For Staff......................................................

//5.3.1 For Displaying Patients Billing Info...................
void display_billing_info(int j,int l){
		system("cls");
		FILE *fp;
		fp = fopen(BILLING, "rb");
		if(fp != NULL){
		fread(billings,sizeof(bill),patient_size,fp);
		}
		else{
			printf("\n\tNo PATIENT found!!!!");
		}
		fclose(fp);
		printf("\n\t---------------------------------------------------------------------------------------------------------\n");
		printf("\tPATIENTS Report DETAILS\n\t---------------------------------------------------------------------------------------------------------");
		printf("\n\tFull Name\tAge\tSex\tBed\tService\tDisease\tCharge\tDischarge");		
	
		printf("\n\t%s\t%d\t%c\t%d\t%s\t%s\t%d\t%c",billings[j].name,billings[j].age,billings[j].sex[0],billings[j].bed,billings[j].service,billings[j].disease,billings[j].charge,billings[j].discharge[0]);
		
		printf("\n\t---------------------------------------------------------------------------------------------------------");
		fclose(fp);
		if(l==0)
		stayin(reception_func);
		else 
		stayin(staff_func);
}


		
//  5.3.2 For Editing Patients's Billing Data.............
	int edit_patient_bill(int a){
	
	char ch[patientinfo_size],cha[patientinfo_size],cha1[patientinfo_size];
	int j,count,choose,x[patient_size],i,k,flag;
	char *ptr, *lname,*fname;
	
	j=1;
	count=0;
	FILE *fp;
	fp = fopen(BILLING, "rb"); 
	if(fp != NULL){
		fread(billings,sizeof(bill),patient_size,fp);
			
		}
		else{
			printf("\n\tFile not found!");
		}
	
	fclose(fp);
				printf("\n\tEnter Full Name:");
				strcpy(cha1,stringinp(patientinfo_size));
					strcpy(ch,cha1);
						ptr = strtok(ch, " ");
						fname = ptr;
						while(ptr != NULL)
						{
							lname= ptr;
							ptr = strtok(NULL, " ");
						}
						
						while(billings[j].age != '\0') {
							if(strcmp(billings[j].name,cha1) == 0 && billings[j].removed[0] != 'Y'){
								count++;
								x[count] = j;
							}
							j = j+1;
						}
						
							
						j=1;
						while(billings[j].age != '\0') {
							i=0;
							while(billings[j].name[i+strlen(fname)-1] != '\0'){
								strncpy(cha,&billings[j].name[i],strlen(fname));
								if((strcmp(cha,fname) == 0) && billings[j].removed[0] != 'Y' ){
									
										flag=0;
										for(k=0;k<=count;k++){
											if(x[k]==j){
												flag=1;
												break;
										}
									}	
										if(flag==0){
											count++;
											x[count] = j; 
										}
								}
								i++;
							}
							j++;	
						}
						
						
						
						j=1;
						while(billings[j].age != '\0') {
							i=0;
							while(billings[j].name[i+strlen(lname)-1] != '\0'){
								strncpy(cha,&billings[j].name[i],strlen(lname));
								if((strcmp(cha,lname) == 0) && billings[j].removed[0] != 'Y' ){
										
										flag=0;
										for(k=0;k<=count;k++){
											if(x[k]==j){
												flag=1;
												break;
										}
									}
										if(flag==0){
											count++;
											x[count] = j; 
										}
								}
								i++;
							}
							j++;	
						}
		
		if(count != 0){
			j = edit_patient_disp_bill(x,count);
			
			edit_patient_edited_bill(j,a);
		
		}
		else{
			printf("\n\tNot  Found!");
				stayin(staff_func);
			
		}
		
	}
	
	
// 5.3.3 For Display Edited Patient's Billing Data.............
int edit_patient_disp_bill(int x[],int count){
		system("cls");
		int i,choose;
				FILE *fp;
				fp = fopen(BILLING, "rb");
					fread(billings,sizeof(bill),patient_size,fp);
					printf("\n\t---------------------------------------------------------------------------------------------------------\n");
					printf("\tSEARCHED PATIENTS DETAILS\n\t---------------------------------------------------------------------------------------------------------");
					
					printf("\n\tFull Name\tAge\tSex\tBed\tService\tDisease\tCharge\tDischarge");		
					for(i=1; i<=count; i++){
						printf("\n\t%s\t%d\t%c\t%d\t%s\t%s\t%d\t%c",billings[x[i]].name,billings[x[i]].age,billings[x[i]].sex[0],billings[x[i]].bed,billings[x[i]].service,billings[x[i]].disease,billings[x[i]].charge,billings[x[i]].discharge[0]);
					}
					
				printf("\n\t---------------------------------------------------------------------------------------------------------");
				printf("\n\tChoose:\n\t0 --> Back");
				for(i=1; i<=count; i++){
					printf("\n\t%d --> Edit %s's Report",i,billings[x[i]].name);
				}
				printf("\n\t");
				wrongsearchedit2:
				choose = choose_str(2);
				if(choose == 0){
					system("cls");
					staff_func();
				} 
				else if(choose>=1 && choose<=count){
				return x[choose];
				}
				else{
					printf("\n\tInvalid Choice.");
					goto wrongsearchedit2;
				}
			fclose(fp);		

}


	
// 5.3.4 For Editing Patient's Billing Data...........
int edit_patient_edited_bill(int j,int k){
		bill billingedit;
		int i=1,l=0,flag=0,m;
		
	FILE *fp;
	fp = fopen(BILLING, "rb"); 
	fread(billings,sizeof(bill),patient_size,fp);
	fclose(fp);
			switch(k){
				case 2:
				case 3:
					printf("\n\tChoose Services:\n\t1 --> OPD\n\t2 --> Emergency\n\t3 --> Operation\n\t4 --> IPD");
					billingservice1:
					m = choose_str(1);
					switch(m){
						case 0:
							system("cls");
							staff_func();
						case 1:
							strcpy(billingedit.service,"OPD");
							break;
						case 2:
							strcpy(billingedit.service,"Emmergency");
							break;
						case 3:
							strcpy(billingedit.service,"Operation");
							break;
						case 4:
							strcpy(billingedit.service,"IPD");
							break;
						default:
							printf("Invalid Choice!");
							goto billingservice1;
					}
					strcpy(billings[j].service,billingedit.service);
					if(k!=2){	
						break;
					}
				case 4:
					
					if(strcmp(billings[j].service,"OPD") !=0 ){
								
						printf("\n\tAvailable Beds\n\t");
						for(l=1; l<totalbed; l++){
						flag=0;
						i=1;
							while(billings[i].age != '\0') {
									if(l==billings[i].bed){
										flag=1;
										break;	
									}
									i++;
							}
							if(flag==0){
							printf("  %d",l);
							}
						}
					
						printf("\n\tEdit Bed(%d):",billings[j].bed);
						billingbed1:
						billingedit.bed = choose_str(2);
						
						if(billingedit.bed ==0){
							system("cls");
							staff_func();
						}
						if(billingedit.bed<1 || billingedit.bed >=totalbed){
							printf("\n\tInvalid Bed Number");
									goto billingbed1;
							}
							else{	
								i=1;
								while(billings[i].age != '\0'){
									if(billings[j].bed==billingedit.bed){
									break;	
									}
									if(billings[i].bed == billingedit.bed){
										printf("\n\tInvalid Bed!!");
										goto billingbed1;
									}
									i++;	
								}
							}
								
						billings[j].bed=billingedit.bed;
					}
					else{
						printf("\n\tOPD service has no bed alloted!");
					}
					if(k!=2){	
						break;
					}
				case 5:
					printf("\n\tEdit Disease:");
					strcpy(billingedit.disease,stringedit(billings[j].disease));
					if(strcmp(billingedit.disease,"0")==0){
							system("cls");
							staff_func();
						}
					strcpy(billings[j].disease,billingedit.disease);
					if(k!=2){	
						break;
					}
				case 6:
					
					printf("\n\tEdit Charge:");
					wrongchargeedit1:
					billingedit.charge = choose_str(5);
					if(billingedit.charge ==0){
							system("cls");
							staff_func();
						}
					if((billingedit.charge < 0 || billingedit.charge > 1000000)){
							printf("\n\tInvalid Charge!!");
							goto wrongchargeedit1;
						}
						
					billings[j].charge=billingedit.charge;
					if(k!=2){	
						break;
					}
				case 7:
					
					printf("\n\tEdit Discharge(Y/N):");
					wrongdischargeedit1:
					strcpy(billingedit.discharge,stringinp(1));
					if((billingedit.discharge[0] != 'Y') && (billingedit.discharge[0] != 'N')){
							printf("\n\tInvalid Choice!!");
							goto wrongdischargeedit1;
						}
					billings[j].charge=billingedit.charge;
					billings[j].discharge[0] =  billingedit.discharge[0];
					break;
				default:
					printf("cant do anything.");	
			
		}
			fp=fopen(BILLING,"wb");
			fwrite(billings,sizeof(bill),patient_size,fp);
			fclose(fp);
		printf("\n\t%s's data Edited Successfully.",billings[j].name);
		getch();
		stayin(staff_func);
}
		
//	

//----------------------------------------------------------------------------------------------

//*******************************************************************************************

