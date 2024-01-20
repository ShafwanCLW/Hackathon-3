/*This program will calculate  the total of patient’s charges which includes hospital stay, surgery charges, pharmacy charges and other 
services charges for each patient
This program also calculate the total of all patients's charge, hospital stay charge, surgery charge, medication charge, average stay per patient,
 highest and lowst bill among patient.
Program:Hospital billing generator v2.0
Develepor: Hariz, Shafwan, Rahimi
Contact: norahimisahal3@student.usm.my
		 syahirulshafwan@student.usm.my
		 muhammadhariznaim@student.usm.my */
#include <iostream> // library 
#include <iomanip> // library
using namespace std;

// Function Prototype
void hospStay(double &,double &, int &, string &, string &);	//function for hospital stay contain room charge, food charge
void surgery(double &, string &);								//function for surgery charge
void service(double &, double &, double &, string &, string &, string &, int &, int &, int &);	//function for 3 service charge
void medicine(double &, double &, double &, double &, double &,
			  string &, string &, string &, string &, string &,
			  int &, int &, int &, int &, int &);	//function for 5 medicine
void showBill(double, double, int, string, string,
			  double, string,
			  double, double, double, string, string, string, int, int, int,
			  double, double, double, double , double , string, string, string, string, string, int, int, int, int, int,
			  double [][5],int,double,string [][2]);	//function for calculate total and receipt,
void totalBill(double[][5], int, string[][2]); //function for calculate total patients bill,total each charge, average stay, lowest and highest bill

void intro();//function for introduction		

int main(){  // main function
	// variables declaration
	

	int day_bill,numofpatient, treatmentFreq_bill1=0,treatmentFreq_bill2=0,treatmentFreq_bill3=0, //variable for day and 3 treatment
		medicineQuant_bill1=0, medicineQuant_bill2=0, medicineQuant_bill3=0, medicineQuant_bill4=0, medicineQuant_bill5=0; //variable for 5 medicine
	double 	roomCharge_bill,foodCharge_bill, //variable for hospital stay charge
			surgeryCharge_bill=0, //vaiable for surgery charge
			serviceCharge_bill1=0, serviceCharge_bill2, serviceCharge_bill3, //variable for 3 service charge
			medicineCharge_bill1=0, medicineCharge_bill2, medicineCharge_bill3, medicineCharge_bill4, medicineCharge_bill5, //variable for 5 medicine charge
			total_bill,total_patientbill,totalSTAY; //variable for total bill
	string	roomName_bill,foodName_bill, //variable for room and food name
			surgeryName_bill, //variable for surgery name
			serviceName_bill1, serviceName_bill2, serviceName_bill3, //variable for 3 service name
			medicineName_bill1, medicineName_bill2, medicineName_bill3, medicineName_bill4, medicineName_bill5; //variable for 5 medicine name
	//Setup numeric output formatting		
	cout<<fixed<<showpoint<<setprecision(2);

	intro(); //function call for intro

	int patientno;// for size of patient number in array
	cout<<"\nNUMBER OF PATIENT TODAY: ";
	cin>>patientno;
	
	string arrname[patientno][2];// each patient index and size of 2 index for name and gender
	double arrprice[patientno][5];// each patient index and size of 5 index for hospital stay, surgery, service, medication, and day 
	string gender;
		
	for(int i=0;i<patientno; i++){
		cout<<"\n__________________________________";		
		cout<<"\nPATIENT "<<(i+1)<<" NAME: ";
		cin.ignore();
		getline(cin, arrname[i][0]);// store each patient name in array 
	
		cout<<"PATIENT "<<(i+1)<<" GENDER (F: FEMALE)(M: MALE): ";
		cin>>gender;
		if(gender=="f" || gender=="F"){ //condition to address the patient
			arrname[i][1]="MRs. ";	//store patient gender in array
		}
		else{
			arrname[i][1]="MR. ";
		}
		
		// Function Call 
		hospStay(roomCharge_bill=0, foodCharge_bill=0, day_bill=0, roomName_bill, foodName_bill); //function call for hosptal stay
		surgery(surgeryCharge_bill=0, surgeryName_bill); //function call for surgery
		service(serviceCharge_bill1=0, serviceCharge_bill2=0, serviceCharge_bill3=0, //function call for service treatment
				serviceName_bill1, serviceName_bill2, serviceName_bill3, 
				treatmentFreq_bill1,treatmentFreq_bill2,treatmentFreq_bill3);
		medicine(medicineCharge_bill1=0, medicineCharge_bill2=0, medicineCharge_bill3=0, medicineCharge_bill4=0, medicineCharge_bill5=0, //function call for medicine
				 medicineName_bill1, medicineName_bill2, medicineName_bill3, medicineName_bill4, medicineName_bill5,
				 medicineQuant_bill1, medicineQuant_bill2, medicineQuant_bill3, medicineQuant_bill4, medicineQuant_bill5);
		
		showBill(roomCharge_bill, foodCharge_bill, day_bill, roomName_bill, foodName_bill, //function call for hospital bill
				 surgeryCharge_bill, surgeryName_bill,
				 serviceCharge_bill1,serviceCharge_bill2, serviceCharge_bill3,
				 serviceName_bill1, serviceName_bill2, serviceName_bill3,
				 treatmentFreq_bill1, treatmentFreq_bill2, treatmentFreq_bill3,
				 medicineCharge_bill1, medicineCharge_bill2, medicineCharge_bill3, medicineCharge_bill4, medicineCharge_bill5,
				 medicineName_bill1, medicineName_bill2, medicineName_bill3, medicineName_bill4, medicineName_bill5,
				 medicineQuant_bill1, medicineQuant_bill2, medicineQuant_bill3, medicineQuant_bill4, medicineQuant_bill5,arrprice,i,totalSTAY,arrname);
				 
	}
	totalBill(arrprice,patientno,arrname);//function call for hospital system bill

	return 0;
}

// Function Definition

void intro(){ //introduction message
	cout<<"\t\t\t############################################################################"<<endl;
	cout<<"\t\t\t                     WELCOME TO MAZIANI'S HOSPITAL                          "<<endl;
	cout<<"\t\t\t############################################################################"<<endl;
	cout<<"\t\t\t                    HOSPITAL BILLING GENERATOR V2.0                         "<<endl;
	cout<<"\t\t\t############################################################################"<<endl;	
}
void hospStay(double &roomCharge,double &foodCharge, int &day, string &roomName, string &setName) //function definition for hospital stay
{
	char roomType, foodSet, stayQ;//variable for choice
	int totalSTAY;
	
	const double deluxe=400.00, //price of room type and food set
				 premium=350.00,
				 adult4=100.00,
				 adult6=90.00,	
				 child4=85.00,
				 specialSet=80.00,
				 standardSet=40.00,
				 budgetSet=20.00;	
				 
				 
	cout<<"\nDid the patient stay at hospital? (ENTER 'Y' IF YES):"; 
	cin>>stayQ; 
	
	if(stayQ=='y'||stayQ=='Y'){ //selection if patient stay at hospital
		cout<<"\nHow many days patient stay? :"; 
		cin>>day;
		//room type menu
		cout << "\n\t " << "__________"  << " " << endl;
		cout << "\t|" << "                              "  << "|" << endl;
		cout << "\t|" << setw(20) << " ROOM TYPES " << setw(11) << "|" << endl;
		cout << "\t|" << "__________" <<"|" <<  endl;
		cout << "\t|" << " 1. Deluxe Room " << setw(15) << "|" << endl;
		cout << "\t|" << " 2. Premium Room " << setw(14) << "|" <<endl;
		cout << "\t|" << " 3. Adult 4 bed " << setw(15) << "|" << endl;
		cout << "\t|" << " 4. Adult 6 bed " << setw(15) << "|" << endl;
		cout << "\t|" << " 5. Child 4 bed "  << setw(15)<< "|" << endl;
		cout << "\t|" << "__________" << "|" << endl;
		
		cout<<"Type of Room? :";
		cin>>roomType;
		//loop if user enter invalid choice
		while ((roomType!='1') && (roomType!='2') && (roomType!='3') && (roomType!='4') && (roomType!='5')){
		cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
		cout<<"Type of Room? :";
		cin>>roomType;
		}
			
		//food set menu
		cout << "\n\t " << "__________"  << " " << endl;
		cout << "\t|" << "                              "  << "|" << endl;
		cout << "\t|" << setw(20) << " FOOD SETS " << setw(11) << "|" << endl;
		cout << "\t|" << "__________" <<"|" <<  endl;
		cout << "\t|" << " 1. Special Set Food " << setw(10) << "|" << endl;
		cout << "\t|" << " 2. Standard Set Food " << setw(9) << "|" <<endl;
		cout << "\t|" << " 3. Budget Set Food " << setw(11) << "|" << endl;
		cout << "\t|" << "__________" << "|" << endl;
		
		cout<<"Set of Food? :";
		cin>>foodSet;
		//loop if user enter invalid choice
		while((foodSet!='1') && (foodSet!='2') && (foodSet!='3')){
		cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
		cout<<"Set of Food? :";
		cin>>foodSet;
		}
		//selection for room type
		if(roomType=='1'){
			roomCharge=deluxe;
			roomName="DELUXE ROOM";
		}
		else if(roomType=='2'){
			roomCharge=premium;
			roomName="PREMIUM ROOM";
		}
		else if(roomType=='3'){
			roomCharge=adult4;
			roomName="ADULT (4 BED) ROOM";
	
		}
		else if(roomType=='4'){
			roomCharge=adult6;
			roomName="ADULT (6 BED) ROOM";
	
		}
		else if(roomType=='5'){
			roomCharge=child4;
			roomName="CHILDREN (4 BED) ROOM";
		}
	
		//selection for food set
			if(foodSet=='1'){
			foodCharge=specialSet;
			setName="SPECIAL SET FOOD";
		}
		else if(foodSet=='2'){
			foodCharge=standardSet;
			setName="STANDARD SET FOOD";
				}
		else if(foodSet=='3'){
			foodCharge=budgetSet;
			setName="BUDGET SET FOOD";
		}
		
	}

}
//function call for surgery
void surgery(double &surgeryCharge, string &surgeryName){
	char surgeryType, surgeryQ;//variable for choice
	//price for surgery
	const double plastic=1400.00;
	const double lasik=12000.00;
	const double pregnant=200.00;
	const double gastric_bypass=55000.00;	
	const double cardiac=30000.00;
	
	cout<<"\n__________________________________";		
	cout<<"\nDid the patient take any surgery? (ENTER 'Y' IF YES):";
	cin>>surgeryQ;
	
	if(surgeryQ=='y'||surgeryQ=='Y'){//selection if there are any surgery
	//surgery menu
		cout << "\n\t " << "__________"  << " " << endl;
		cout << "\t|" << "                              "  << "|" << endl;	
		cout << "\t|" << setw(20) << " SURGERY " << setw(11) << "|" << endl;
		cout << "\t|" << "__________" <<"|" <<  endl;
		cout << "\t|" << " 1. Plastic Surgery " << setw(11) << "|" << endl;
		cout << "\t|" << " 2. Lasik Surgery " << setw(13) << "|" <<endl;
		cout << "\t|" << " 3. Pregnant Surgery " << setw(10) << "|" << endl;
		cout << "\t|" << " 4. Gastric Bypass Surgery " << setw(4) << "|" << endl;
		cout << "\t|" << " 5. Cardiac Surgery "  << setw(11)<< "|" << endl;
		cout << "\t|" << "__________" << "|" << endl;
		
		cout<<"Type of surgery? :";
		cin>>surgeryType;
		//loop if user enter invalid value
		while ((surgeryType!='1') && (surgeryType!='2') && (surgeryType!='3') && (surgeryType!='4') && (surgeryType!='5')){
		cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
		cout<<"Type of surgery? :";
		cin>>surgeryType;
		
		}
		if(surgeryType=='1'){//selection for surgery
			surgeryCharge=plastic;
			surgeryName="PLASTIC SURGERY.";
		}
		else if(surgeryType=='2'){
			surgeryCharge=lasik;
			surgeryName="LASIK SURGERY.";
		}
		else if(surgeryType=='3'){
			surgeryCharge=pregnant;
			surgeryName="PREGNANT SURGERY.";
		}
		else if(surgeryType=='4'){
			surgeryCharge=gastric_bypass;
			surgeryName="GASTRIC BYPASS SURGERY.";
		}
		else if(surgeryType=='5'){
			surgeryCharge=cardiac;
			surgeryName="CARDIAC SURGERY.";
		}
	}
}
//function calling for service
void service(double &serviceCharge1, double &serviceCharge2, double &serviceCharge3,
			 string &serviceName1, string &serviceName2, string &serviceName3,
			 int &treatmentFreq1, int &treatmentFreq2, int &treatmentFreq3){
	char serviceType, choice, serviceQ;//variable for choice
	//price of service
	const double xray=30.00;
	const double diabetic=70.00;
	const double physiotherapy=10.00;
	
	cout<<"\n__________________________________";		
	cout<<"\nDid the patient use any service? (ENTER 'Y' IF YES):";
	cin>>serviceQ;
	
	if(serviceQ=='y' || serviceQ=='Y'){//selection if there is any service
	
		//service menu
		cout << "\n\t " << "__________"  << " " << endl;
		cout << "\t|" << "                              "  << "|" << endl;	
		cout << "\t|" << setw(22) << " EXTRA SERVICE " << setw(9) << "|" << endl;
		cout << "\t|" << "__________" <<"|" <<  endl;
		cout << "\t|" << " 1. X_ray " << setw(21) << "|" << endl;
		cout << "\t|" << " 2. Diabetic " << setw(18) << "|" <<endl;
		cout << "\t|" << " 3. Physiotherapy " << setw(13) << "|" << endl;
		cout << "\t|" << "__________" << "|" << endl;
		
		cout<<"Extra service? :";
		cin>>serviceType;//1st input for service
	//loop if user enters invalid value
		while ((serviceType!='1') && (serviceType!='2') && (serviceType!='3')){
			cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
			cout<<"Extra service? :";
			cin>>serviceType;
		}
		
		
		if(serviceType=='1'){//selection for service
			serviceCharge1=xray;
			serviceName1="X-RAY /TREATMENT";
		}
		else if(serviceType=='2'){
			serviceCharge1=diabetic;
			serviceName1="DIABETIC PROFILE /TEST";
		}
		else if(serviceType=='3'){
			serviceCharge1=physiotherapy;
			serviceName1="PHYSIOTHERAPHY /THERAPHY";
		}
	
		cout<<"How frequent is the service? :";
		cin>>treatmentFreq1;
		
	
		cout<<"Add other Service? (ENTER 'Y' IF YES): ";
		cin>>choice;
		if(choice=='y'){
			cout<<"\nSecond Extra service? :";
			cin>>serviceType;//2nd input for service
	
			while ((serviceType!='1') && (serviceType!='2') && (serviceType!='3')){
				cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
				cout<<"\nSecond Extra service? :";
				cin>>serviceType;
			}
		
			if(serviceType=='1'){
				serviceCharge2=xray;
				serviceName2="X-RAY /TREATMENT";
			}
			else if(serviceType=='2'){
				serviceCharge2=diabetic;
				serviceName2="DIABETIC PROFILE /TEST";
			}
			else if(serviceType=='3'){
				serviceCharge2=physiotherapy;
				serviceName2="PHYSIOTHERAPHY /THERAPHY";
			}	
			cout<<"How frequent is the second service? :";
			cin>>treatmentFreq2;
			
			cout<<"Add other Service? (ENTER 'Y' IF YES)";
			cin>>choice;
			if(choice=='y'){
				cout<<"\nThird Extra service? :";
				cin>>serviceType;//3rd input for service
		
				while ((serviceType!='1') && (serviceType!='2') && (serviceType!='3')){
					cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
					cout<<"\nThird Extra service? :";
					cin>>serviceType;
				}
			
				if(serviceType=='1'){
					serviceCharge3=xray;
					serviceName3="X-RAY /TREATMENT";
				}
				else if(serviceType=='2'){
					serviceCharge3=diabetic;
					serviceName3="DIABETIC PROFILE /TEST";
				}
				else if(serviceType=='3'){
					serviceCharge3=physiotherapy;
					serviceName3="PHYSIOTHERAPHY /THERAPHY";
				}	
				cout<<"How frequent is the third service? :";
				cin>>treatmentFreq3;		
			}				
		}
	}
	
}
//function call for medicine
void medicine(double &medicineCharge1, double &medicineCharge2, double &medicineCharge3, double &medicineCharge4, double &medicineCharge5,
			  string &medicineName1, string &medicineName2, string &medicineName3, string &medicineName4, string &medicineName5,
			  int &medicineQuant1, int &medicineQuant2, int &medicineQuant3, int &medicineQuant4, int &medicineQuant5){
			
		char medicineType, choice, medicineQ;//variable for choice
		//price for medicine
		const double ibuprofen=10.00;
		const double alprazolam=520.00;
		const double naproxen=950.00;
		const double lisinopril=185.00;	
		const double lamotrigin=80.10;
		
	cout<<"\n__________________________________";		
		cout<<"\nDid the patient take any medicine? (ENTER 'Y' IF YES):";
		cin>>medicineQ;
		
		if(medicineQ=='y' || medicineQ=='Y'){
		
		//medicine menu
			cout << "\n\t " << "______________________"  << " " << endl;
			cout << "\t|" << "                                                                  "  << "|" << endl;
			cout << "\t|" << setw(20) << " MEDICATION " << setw(9) << "|" << setw(14) << " WEIGHT(gm) " << setw(3) << "|" << setw(17) 
				 << " TABLET(PACK) " << setw(4) << "|" << endl;
			cout << "\t|" << "______________________" <<"|" <<  endl;
			cout << "\t|" << " 1. Ibuprofen " << setw(15) << "|" << setw(11) << " 200.0 " << setw(6) << "|" << setw(12) << " 200 " << setw(9) << "|" << endl;
			cout << "\t|" << " 2. Alprazolam " << setw(14) << "|" << setw(11) << " 0.5 " << setw(6) << "|" << setw(12) << " 500 " << setw(9) << "|"  << endl;
			cout << "\t|" << " 3. Naproxen " << setw(16) << "|" << setw (11) << " 250.0 " << setw(6) << "|" << setw(12) << " 1000 " << setw(9) << "|" << endl;
			cout << "\t|" << " 4. Lisinopril " << setw(14) << "|" << setw(11) << " 5.0 " << setw(6) << "|" << setw(12) << " 500 " << setw(9) << "|"  << endl;
			cout << "\t|" << " 5. Lamotrigin " << setw(14) << "|" << setw(11) << " 50.0 " << setw(6) << "|" << setw(12) << " 30 " << setw(9) << "|"  << endl;
			cout << "\t|" << "______________________" << "|" << endl;
				
			cout<<"Medicine Type : ";
			cin>>medicineType;
			//loop if user enters invalid value
			while ((medicineType!='1') && (medicineType!='2') && (medicineType!='3') && (medicineType!='4') && (medicineType!='5')){
			cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
			cout<<"Medicine Type : ";
			cin>>medicineType;//1st input for medicine
			}
			
			if(medicineType=='1'){//selection for medicine
				medicineCharge1=ibuprofen;
				medicineName1="IBUPROFEN 200mg , 20 TABLET / PACK";
			}
			else if(medicineType=='2'){
				medicineCharge1=alprazolam;
				medicineName1="ALPRAZOLAM 0.5mg , 500 TABLET / PACK";
			}
			else if(medicineType=='3'){
				medicineCharge1=naproxen;
				medicineName1="NAPROXEN 250mg , 1000 TABLET / PACK";
			}
			else if(medicineType=='4'){
				medicineCharge1=lisinopril;
				medicineName1="LISINOPRIL 5mg , 500 TABLET / PACK";
			}
			else if(medicineType=='5'){
				medicineCharge1=lamotrigin;
				medicineName1="LAMOTRIGIN 50mg , 30 TABLET / PACK";
			}
			cout<<"Medicine Quantity :";
			cin>>medicineQuant1;
			//2nd input for medicine
			cout<<"Add other Medicine? (ENTER 'Y' IF YES): ";
			cin>>choice;
			if(choice=='y'){
				cout<<"\nSecond Medicine Type : ";
				cin>>medicineType;
				
				while ((medicineType!='1') && (medicineType!='2') && (medicineType!='3') && (medicineType!='4') && (medicineType!='5')){
				cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
				cout<<"Second Medicine Type : ";
				cin>>medicineType;
				}
				
				if(medicineType=='1'){
					medicineCharge2=ibuprofen;
					medicineName2="IBUPROFEN 200mg , 20 TABLET / PACK";
				}
				else if(medicineType=='2'){
					medicineCharge2=alprazolam;
					medicineName2="ALPRAZOLAM 0.5mg , 500 TABLET / PACK";
				}
				else if(medicineType=='3'){
					medicineCharge2=naproxen;
					medicineName2="NAPROXEN 250mg , 1000 TABLET / PACK";
				}
				else if(medicineType=='4'){
					medicineCharge2=lisinopril;
					medicineName2="LISINOPRIL 5mg , 500 TABLET / PACK";
				}
				else if(medicineType=='5'){
					medicineCharge2=lamotrigin;
					medicineName2="LAMOTRIGIN 50mg , 30 TABLET / PACK";
				}
				cout<<"Second Medicine Quantity :";
				cin>>medicineQuant2;	
				
				//3rd input for medicine
				cout<<"Add other Medicine? (ENTER 'Y' IF YES):";
				cin>>choice;
				if(choice=='y'){
					cout<<"\nThird Medicine Type : ";
					cin>>medicineType;
					
					while ((medicineType!='1') && (medicineType!='2') && (medicineType!='3') && (medicineType!='4') && (medicineType!='5')){
					cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
					cout<<"Third Medicine Type : ";
					cin>>medicineType;
					}
					
					if(medicineType=='1'){
						medicineCharge3=ibuprofen;
						medicineName3="IBUPROFEN 200mg , 20 TABLET / PACK";
					}
					else if(medicineType=='2'){
						medicineCharge3=alprazolam;
						medicineName3="ALPRAZOLAM 0.5mg , 500 TABLET / PACK";
					}
					else if(medicineType=='3'){
						medicineCharge3=naproxen;
						medicineName3="NAPROXEN 250mg , 1000 TABLET / PACK";
					}
					else if(medicineType=='4'){
						medicineCharge3=lisinopril;
						medicineName3="LISINOPRIL 5mg , 500 TABLET / PACK";
					}
					else if(medicineType=='5'){
						medicineCharge3=lamotrigin;
						medicineName3="LAMOTRIGIN 50mg , 30 TABLET / PACK";
					}
					cout<<"Third Medicine Quantity :";
					cin>>medicineQuant3;
					
					//4th input for medicine
					cout<<"Add other Medicine? (ENTER 'Y' IF YES): ";
					cin>>choice;
					if(choice=='y'){
						cout<<"\nFourth Medicine Type : ";
						cin>>medicineType;
									
						
						while ((medicineType!='1') && (medicineType!='2') && (medicineType!='3') && (medicineType!='4') && (medicineType!='5')){
						cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
						cout<<"Fourth Medicine Type : ";
						cin>>medicineType;
						}
						
						if(medicineType=='1'){
							medicineCharge4=ibuprofen;
							medicineName4="IBUPROFEN 200mg , 20 TABLET / PACK";
						}
						else if(medicineType=='2'){
							medicineCharge4=alprazolam;
							medicineName4="ALPRAZOLAM 0.5mg , 500 TABLET / PACK";
						}
						else if(medicineType=='3'){
							medicineCharge4=naproxen;
							medicineName4="NAPROXEN 250mg , 1000 TABLET / PACK";
						}
						else if(medicineType=='4'){
							medicineCharge4=lisinopril;
							medicineName4="LISINOPRIL 5mg , 500 TABLET / PACK";
						}
						else if(medicineType=='5'){
							medicineCharge4=lamotrigin;
							medicineName4="LAMOTRIGIN 50mg , 30 TABLET / PACK";
						}
						cout<<"Fourth Medicine Quantity :";
						cin>>medicineQuant4;						
						
						//5th input for medicine
						cout<<"Add other Medicine? (y/n) : ";
						cin>>choice;
						if(choice=='y'){
							cout<<"\nFifth Medicine Type : ";
							cin>>medicineType;
							
							while ((medicineType!='1') && (medicineType!='2') && (medicineType!='3') && (medicineType!='4') && (medicineType!='5')){
							cout<<"!WRONG INPUT! PLEASE ENTER VALID CHOICE"<<endl;
							cout<<"Medicine Type : ";
							cin>>medicineType;
							}
							
							if(medicineType=='1'){
								medicineCharge5=ibuprofen;
								medicineName5="IBUPROFEN 200mg , 20 TABLET / PACK";
							}
							else if(medicineType=='2'){
								medicineCharge5=alprazolam;
								medicineName5="ALPRAZOLAM 0.5mg , 500 TABLET / PACK";
							}
							else if(medicineType=='3'){
								medicineCharge5=naproxen;
								medicineName5="NAPROXEN 250mg , 1000 TABLET / PACK";
							}
							else if(medicineType=='4'){
								medicineCharge5=lisinopril;
								medicineName5="LISINOPRIL 5mg , 500 TABLET / PACK";
							}
							else if(medicineType=='5'){
								medicineCharge5=lamotrigin;
								medicineName5="LAMOTRIGIN 50mg , 30 TABLET / PACK";
							}
							cout<<"Fifth Medicine Quantity :";
							cin>>medicineQuant5;
						}								
					}
				}					
			}
	}
}

//function definition  for hospital calculation & bill
void showBill(double roomCharge_bill, double foodCharge_bill, int day_bill, string roomName_bill, string foodName_bill, //value on hospStay function
			  double surgeryCharge_bill, string surgeryName_bill, //value on surgery function 
			  double serviceCharge_bill1, double serviceCharge_bill2, double serviceCharge_bill3,  
			  string serviceName_bill1 , string serviceName_bill2, string serviceName_bill3, //value on treatment function
			  int treatmentFreq_bill1, int treatmentFreq_bill2,int treatmentFreq_bill3,
			  //value on medicine function
			  double medicineCharge_bill1, double medicineCharge_bill2, double medicineCharge_bill3, double medicineCharge_bill4, double medicineCharge_bill5, 
			  string medicineName_bill1, string medicineName_bill2, string medicineName_bill3, string medicineName_bill4, string medicineName_bill5,
			  int medicineQuant_bill1, int medicineQuant_bill2, int medicineQuant_bill3, int medicineQuant_bill4, int medicineQuant_bill5,
			  double arrprice[][5],int i,double totalSTAY, string arrname[][2]){ //calling value needed in showBill funct
			  	
			     	double total_bill, medicineCharge, serviceCharge; //variable use in calculation
			    
			  		cout<<"\n\n\t\t\t--------------------------------HOSPITAL BILL-------------------------------\n\n";
			  		
			  		cout<<"\t\t\t\tPatient Name: "<<arrname[i][1]<<arrname[i][0]<<endl;
			  		cout<<"\t\t\t\tHospital Stay: "<<day_bill<<" days"<<endl<<endl<<endl;
			  		
			  		
					cout<<"\t\t\t\tDESCRIPTION\t\t\t\t\t\tAMOUNT(RM)\n"<<endl;
			  		
			  		//selection if there any hospital stay 
			  		if(day_bill!=0){
						cout<<"\t\t\t\t"<<roomName_bill<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<roomCharge_bill<<endl;
						cout<<"\t\t\t\t"<<foodName_bill<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<foodCharge_bill<<endl;
					}
					
					//selection if there any surgery
					if(surgeryCharge_bill!=0){
						cout<<"\t\t\t\t"<<surgeryName_bill<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<surgeryCharge_bill<<endl;
					}
					
					//selection if there any treatment service
					if(serviceCharge_bill1!=0){					
						cout<<"\t\t\t"<<treatmentFreq_bill1<<"X\t"<<serviceName_bill1<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<serviceCharge_bill1*treatmentFreq_bill1<<endl;
						if(treatmentFreq_bill2!=0){//include if there're second treatment
							cout<<"\t\t\t"<<treatmentFreq_bill2<<"X\t"<<serviceName_bill2<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<serviceCharge_bill2*treatmentFreq_bill2<<endl;
						}
						if(treatmentFreq_bill3!=0){//include if there're third treatment
							cout<<"\t\t\t"<<treatmentFreq_bill3<<"X\t"<<serviceName_bill3<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<serviceCharge_bill3*treatmentFreq_bill3<<endl;
						}
					}
					
					//selection if there any medicine 
					if(medicineCharge_bill1!=0){
						cout<<"\t\t\t"<<medicineQuant_bill1<<"X\t"<<medicineName_bill1<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<medicineCharge_bill1*medicineQuant_bill1<<endl;
						if(medicineQuant_bill2!=0){//include if there're second med
							cout<<"\t\t\t"<<medicineQuant_bill2<<"X\t"<<medicineName_bill2<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<medicineCharge_bill2*medicineQuant_bill2<<endl;
						}
						if(medicineQuant_bill3!=0){//include if there're third med
							cout<<"\t\t\t"<<medicineQuant_bill3<<"X\t"<<medicineName_bill3<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<medicineCharge_bill3*medicineQuant_bill3<<endl;
						}					
						if(medicineQuant_bill4!=0){//include if there're fourth med
							cout<<"\t\t\t"<<medicineQuant_bill4<<"X\t"<<medicineName_bill4<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<medicineCharge_bill4*medicineQuant_bill4<<endl;
						}	
						if(medicineQuant_bill5!=0){//include if there're fifth med
							cout<<"\t\t\t"<<medicineQuant_bill5<<"X\t"<<medicineName_bill5<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<medicineCharge_bill5*medicineQuant_bill5<<endl;
						}
					}
					
					//calculation
					//total service charge only
					serviceCharge=(serviceCharge_bill1*treatmentFreq_bill1)+(serviceCharge_bill2*treatmentFreq_bill2)+(serviceCharge_bill3*treatmentFreq_bill3);
					medicineCharge=(medicineCharge_bill1*medicineQuant_bill1)+(medicineCharge_bill2*medicineQuant_bill2)+(medicineCharge_bill3*medicineQuant_bill3)+
								   (medicineCharge_bill4*medicineQuant_bill4)+(medicineCharge_bill5*medicineQuant_bill5);//total medicine charge only
					totalSTAY=(roomCharge_bill+foodCharge_bill)*day_bill;
					total_bill=totalSTAY+surgeryCharge_bill+serviceCharge+medicineCharge;//total bill
					//declaration for each arrprice array
					arrprice[i][0]=totalSTAY;
					arrprice[i][1]=surgeryCharge_bill;
					arrprice[i][2]=serviceCharge;
					arrprice[i][3]=medicineCharge;
					arrprice[i][4]=day_bill;
					//view total bill
					cout<<"\t\t\t----------------------------------------------------------------------------"<<endl;										
					cout<<"\t\t\t\tTOTAL BILL\t\t\t\t\t\tRM"<<total_bill<<endl;
					cout<<"\t\t\t\t----------\t\t\t\t\t\t----------"<<endl<<endl<<endl;																			
			  }
//function definition for each patient data			  
void totalBill(double arrprice[][5], int patientno, string arrname[][2])
{
	double Totalstay=0,Totalsurgery=0,Totalservice=0,Totalmedicine=0,total_patientbill=0,patient_bill,averagestay,Totalday=0,maximum,minimum=999999;
	string maximumName, minimumName;//highest and lowest patient name
	for(int i=0; i<patientno;i++){//condition to calculate every total charge based on each patient 
		patient_bill=0;
		Totalstay+=arrprice[i][0];//calcualtion for total stay charge;
		Totalsurgery+=arrprice[i][1];//calculation for total surgery charge
		Totalservice+=arrprice[i][2];//calculation for total service charge
		Totalmedicine+=arrprice[i][3];//calculation for total medication charge
		Totalday+=arrprice[i][4];//calcualtion for total hospital stay all patient
		


		for(int j=0; j<4; j++)
		{
			patient_bill += arrprice[i][j];
		}
		total_patientbill+=patient_bill;// to calculate total bill all patient
		
		averagestay=Totalday/patientno;// to calculate average hospital stay per patient
		
		if(patient_bill>maximum)//finding highest hospital bill among all patient
		{
			maximum=patient_bill;
			maximumName = arrname[i][1]+arrname[i][0];
		}
		if(patient_bill<minimum)//finding lowest hospital bill among all patient
		{
			minimum=patient_bill;
			minimumName = arrname[i][1]+arrname[i][0];
		}

			
	}
	//patient bill information print out
	cout<<"\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";		
	cout<<"\n\n\t\t\t---------------------------PATIENT BILL INFORMATON--------------------------\n\n";
	cout<<"\n\t\t\t____________________________\n\n";	
	cout<<"\t\t\t                                PATIENT LIST                                \n\n";

		
	for(int i=0; i<patientno;i++){
		cout<<"\t\t\tPatient "<<(i+1)<<":\n\t\t\t\t\t\t\t\t\t\t\t"<<arrname[i][1]<<arrname[i][0]<<endl;//viewing patient detail
	}
	cout<<"\t\t\tTotal Patient "<<" :\n\t\t\t\t\t\t\t\t\t\t\t"<<patientno<<endl<<endl;	
	//viewing charge detail
	cout<<"\n\t\t\t____________________________\n\n";		
	
	cout<<"\t\t\tTotal Surgery Charge for "<<patientno<<" Patients :\n\t\t\t\t\t\t\t\t\t\t\tRM"<<Totalsurgery<<endl<<endl;	
	cout<<"\t\t\tTotal Service Charge for "<<patientno<<" Patients :\n\t\t\t\t\t\t\t\t\t\t\tRM"<<Totalservice<<endl<<endl;	
	cout<<"\t\t\tTotal Medicine Charge for "<<patientno<<" Patients :\n\t\t\t\t\t\t\t\t\t\t\tRM"<<Totalmedicine<<endl<<endl;
	cout<<"\t\t\tTotal Charge Of "<<patientno<<" Patients :\n\t\t\t\t\t\t\t\t\t\t\tRM"<<total_patientbill<<endl<<endl;
	//viewing average hospital stay, lowest and highest charge
	cout<<"\n\t\t\t____________________________\n\n"<<endl;		
	cout<<"\t\t\tAverage Hospital Stay Of "<<patientno<<" Patients :\n\t\t\t\t\t\t\t\t\t\t\t"<<static_cast<int>(averagestay)<<endl<<endl;
	cout<<"\t\t\tHighest Bill Charge : "<<"\n\t\t\t\t\t\t\t\t\t\t\t"<<maximumName<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<maximum<<endl<<endl;
	cout<<"\t\t\tLowest Bill Charge : "<<"\n\t\t\t\t\t\t\t\t\t\t\t"<<minimumName<<"\n\t\t\t\t\t\t\t\t\t\t\tRM"<<minimum<<endl<<endl;
	
}
