// 12DOF-Q-3-GeekServo-ref  - 21/07/2022 - Reference version
void(* resetFunc) (void) = 0;               // soft reset function
#include <Servo.h>
int pb=A0,Speed=1000;
unsigned long start;
const int nb=12;                            // Number of servos
Servo Srv[nb];                              // Servos table
int Smin[nb]={ 495, 490, 495, 490, 505, 485, 485, 485, 495, 495, 485, 485}; // servos values for 0°
int Smax[nb]={1500,1505,1510,1485,1510,1500,1495,1500,1490,1495,1500,1500}; // servos values for 180°
int OnOff[nb]={1,1,1,1,1,1,1,1, 1,1,1,1};   // on/off Servos table
int FRLS=0, FRRS=1, FLLS=2, FLRS=3, BRLS=4, BRRS=5, BLLS=6, BLRS=7, FRS=8, FLS=9, BRS=10, BLS=11;
//***************** errors correction servos position  ************************************************************************************
// servos      FRLS  FRRS  FLLS  FLRS  BRLS  BRRS  BLLS  BLRS  FRS  FLS  BRS  BLS    you must modify these values according to your servos
int Err[nb]={    0,    0,    0,   -4,    5,   -5,    0,    0,   0,   0,   0,  -3    };  
//**************************************************************-****+****+****-***********************************************************
         
void  setup() {
  delay(400);                   // for reset consideration
  Serial.begin(9600);
  pinMode(pb,INPUT_PULLUP);     // start/stop/reset button attachment

  int a=60, b=90;               // Servos angle initialization
  if(OnOff[FRLS]) { Srv[FRLS].attach(2,Smin[FRLS],Smax[FRLS]); Srv[FRLS].writeMicroseconds(map(    a+Err[FRLS],0,180,Smin[FRLS],Smax[FRLS])); } // FR Front Right leg - LS Left   Servo
  if(OnOff[FRRS]) { Srv[FRRS].attach(3,Smin[FRRS],Smax[FRRS]); Srv[FRRS].writeMicroseconds(map(180-a+Err[FRRS],0,180,Smin[FRRS],Smax[FRRS])); } // FR Front Right leg - RS Right  Servo
  if(OnOff[FLLS]) { Srv[FLLS].attach(4,Smin[FLLS],Smax[FLLS]); Srv[FLLS].writeMicroseconds(map(    a+Err[FLLS],0,180,Smin[FLLS],Smax[FLLS])); } // FL Front Left  leg - LS Left   Servo
  if(OnOff[FLRS]) { Srv[FLRS].attach(5,Smin[FLRS],Smax[FLRS]); Srv[FLRS].writeMicroseconds(map(180-a+Err[FLRS],0,180,Smin[FLRS],Smax[FLRS])); } // FL Front Left  leg - RS Right  Servo
  if(OnOff[BRLS]) { Srv[BRLS].attach(6,Smin[BRLS],Smax[BRLS]); Srv[BRLS].writeMicroseconds(map(    a+Err[BRLS],0,180,Smin[BRLS],Smax[BRLS])); } // BR Back  Right leg - LS Left   Servo
  if(OnOff[BRRS]) { Srv[BRRS].attach(7,Smin[BRRS],Smax[BRRS]); Srv[BRRS].writeMicroseconds(map(180-a+Err[BRRS],0,180,Smin[BRRS],Smax[BRRS])); } // BR Back  Right leg - RS Right  Servo
  if(OnOff[BLLS]) { Srv[BLLS].attach(8,Smin[BLLS],Smax[BLLS]); Srv[BLLS].writeMicroseconds(map(    a+Err[BLLS],0,180,Smin[BLLS],Smax[BLLS])); } // BL Back  Left  leg - LS Left   Servo
  if(OnOff[BLRS]) { Srv[BLRS].attach(9,Smin[BLRS],Smax[BLRS]); Srv[BLRS].writeMicroseconds(map(180-a+Err[BLRS],0,180,Smin[BLRS],Smax[BLRS])); } // BL Back  Left  leg - RS Right  Servo
  if(OnOff[FRS])  { Srv[FRS].attach(10,Smin[FRS],Smax[FRS]); Srv[FRS].writeMicroseconds(map(b-Err[FRS],0,180,Smin[FRS],Smax[FRS])); }           // FRS Front Right Shoulder   Servo
  if(OnOff[FLS])  { Srv[FLS].attach(11,Smin[FLS],Smax[FLS]); Srv[FLS].writeMicroseconds(map(b+Err[FLS],0,180,Smin[FLS],Smax[FLS])); }           // FLS Front Left  Shoulder   Servo
  if(OnOff[BRS])  { Srv[BRS].attach(12,Smin[BRS],Smax[BRS]); Srv[BRS].writeMicroseconds(map(b+Err[BRS],0,180,Smin[BRS],Smax[BRS])); }           // BRS Back  Right Shoulder   Servo
  if(OnOff[BLS])  { Srv[BLS].attach(13,Smin[BLS],Smax[BLS]); Srv[BLS].writeMicroseconds(map(b-Err[BLS],0,180,Smin[BLS],Smax[BLS])); }           // BLS Back  Left  Shoulder   Servo

  Serial.print("\n\t To start, click on the Start button");  while( digitalRead(pb) );  delay(400);  Serial.print("\n\t Started");
}

void loop() { // uncomment one or more of the following lines to test gaits
//  for( int i=0;i<=11;i++) { Speed=7500; Turn('R'); }  Speed=9000; Turn('R');  delay(250); // Right spin spot
//  for( int i=0;i<=11;i++) { Speed=7500; Turn('L'); }  Speed=9000; Turn('L');  delay(250); // Left spin spot
//  for( int i=0;i<=16;i++) { Speed=1800; Walk( 20); }  Speed=4500; Walk( 20);  delay(250); // 20=forward turn right
//  for( int i=0;i<=16;i++) { Speed=1800; Walk( 70); }  Speed=4500; Walk( 70);  delay(250); // 70=forward turn left
//  for( int i=0;i<= 8;i++) { Speed=1800; Walk( 45); }  Speed=4500; Walk( 45);  delay(250); // 45=forward straight
//  for( int i=0;i<= 8;i++) { Speed=1800; Walk(225); }  Speed=4500; Walk(225);  delay(250); // 225=backward straight
//  for( int i=0;i<=11;i++) { Speed=1500; Shift('R'); } Speed=4500; Shift('R'); delay(250); // right sided gait 
//  for( int i=0;i<=11;i++) { Speed=1500; Shift('L'); } Speed=4500; Shift('L'); delay(250); // left sided gait
}

void Walk( int a){
  // Value of a
  // Forward  : from  15 to  44 turn right,  45 straight forward,   from  75 to  46 turn left
  // Backward : from 195 to 224 turn left,  225 straight Backward,  from 255 to 226 turn right
  // Left spin spot : 135  ,  Right spin spot : 315
  
  int FRx[]= {  0,-10,-20,-30,-40,-50,-63,    -63,-50,-40,-30,-20,-10,  0, 10, 20, 30, 40, 50, 63, 63, 50, 40, 30, 20, 10};
  int FLx[]= {  0, 10, 20, 30, 40, 50, 63,     63, 50, 40, 30, 20, 10,  0,-10,-20,-30,-40,-50,-63,-63,-50,-40,-30,-20,-10};
  int BRx[]= {  0, 10, 20, 30, 40, 50, 63,     63, 50, 40, 30, 20, 10,  0,-10,-20,-30,-40,-50,-63,-63,-50,-40,-30,-20,-10};
  int BLx[]= {  0,-10,-20,-30,-40,-50,-63,    -63,-50,-40,-30,-20,-10,  0, 10, 20, 30, 40, 50, 63, 63, 50, 40, 30, 20, 10};
  
  int FRy[]= {-10,-10,-10,-10,-10,-10,-10,     10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,-10,-10,-10,-10,-10,-10};
  int FLy[]= { 10, 10, 10, 10, 10, 10, 10,    -10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10, 10, 10, 10, 10, 10, 10};
  int BRy[]= { 10, 10, 10, 10, 10, 10, 10,    -10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10, 10, 10, 10, 10, 10, 10};
  int BLy[]= {-10,-10,-10,-10,-10,-10,-10,     10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,-10,-10,-10,-10,-10,-10};
  
  int FRz[]= {  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
  int FLz[]= {  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
  int BRz[]= {  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};
  int BLz[]= {  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};

  int lgTab = sizeof(FRx)/sizeof(int);
  int i=0, j=lgTab-1;
  float S=sin(a*PI/180), C=cos(a*PI/180); //Serial.print(String()+("\n")+("\t a = ")+a+("\t S = ")+S+("\t C = ")+C);

  for( i;i<=j;i++){
    IK(+FRx[abs(i)]*S,FRy[abs(i)],-FRz[abs(i)],FRLS,FRRS,FRS);   // Front Right Leg
    IK(-FLx[abs(i)]*C,FLy[abs(i)],+FLz[abs(i)],FLLS,FLRS,FLS);   // Front Left  Leg
    IK(+BRx[abs(i)]*S,BRy[abs(i)],+BRz[abs(i)],BRLS,BRRS,BRS);   // Back  Right Leg
    IK(-BLx[abs(i)]*C,BLy[abs(i)],-BLz[abs(i)],BLLS,BLRS,BLS);   // Back  Left  Leg
  }
}

void Shift(char c){ // Right c = 'R'   Left c = 'L'
  int FRx[]= {  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0};
  int FLx[]= {  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0};
  int BRx[]= {  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0};
  int BLx[]= {  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0};
  
  int FRy[]= {-10,-10,-10,-10,-10,-10,-10,-10,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    -10,-10,-10,-10,-10,-10,-10};
  int FLy[]= {  0,  0,  0,  0,  0,  0,  0,  0,    -20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,      0,  0,  0,  0,  0,  0,  0};
  int BRy[]= {  0,  0,  0,  0,  0,  0,  0,  0,    -10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,      0,  0,  0,  0,  0,  0,  0};
  int BLy[]= {-20,-20,-20,-20,-20,-20,-20,-20,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    -20,-20,-20,-20,-20,-20,-20};
  
  int FRz[]= {  0, -5,-10,-15,-20,-25,-30,-35,    -35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35,     35, 30, 25, 20, 15, 10,  5};
  int FLz[]= {  0, -5,-10,-15,-20,-25,-30,-35,    -35,-30,-25,-20,-15,-10, -5,  0,  5, 10, 15, 20, 25, 30, 35,     35, 30, 25, 20, 15, 10,  5};
  int BRz[]= {  0,  5, 10, 15, 20, 25, 30, 35,     35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,    -35,-30,-25,-20,-15,-10, -5};
  int BLz[]= {  0,  5, 10, 15, 20, 25, 30, 35,     35, 30, 25, 20, 15, 10,  5,  0, -5,-10,-15,-20,-25,-30,-35,    -35,-30,-25,-20,-15,-10, -5};
 
  int lgTab = sizeof(FRx)/sizeof(int);
  int i=0, j=lgTab-1;  if(c=='L'){  i=-(lgTab-1); j=0; }
  for( i;i<=j;i++){
    IK(+FRx[abs(i)],FRy[abs(i)],-FRz[abs(i)],FRLS,FRRS,FRS);   // Front Right Leg
    IK(-BLx[abs(i)],BLy[abs(i)],-BLz[abs(i)],BLLS,BLRS,BLS);   // Back Left Leg
    IK(-FLx[abs(i)],FLy[abs(i)],+FLz[abs(i)],FLLS,FLRS,FLS);   // Front Left Leg
    IK(+BRx[abs(i)],BRy[abs(i)],+BRz[abs(i)],BRLS,BRRS,BRS);   // Back Right Leg
  }
}

void Turn(char c){    // Turn Right c = 'R'   Turn Left c = 'L'
  int FRx[]= {  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0};
  int FLx[]= {  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0};
  int BRx[]= {  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0};
  int BLx[]= {  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,  0,  0,  0,  0,  0,  0,  0,  0};
  
  int FRy[]= { 10, 10, 10, 10, 10, 10, 10, 10, 10,    -10,-10,-10,-10,-10,-10,-10,-10,-10};
  int FLy[]= {-10,-10,-10,-10,-10,-10,-10,-10,-10,     10, 10, 10, 10, 10, 10, 10, 10, 10};
  int BRy[]= {-10,-10,-10,-10,-10,-10,-10,-10,-10,     10, 10, 10, 10, 10, 10, 10, 10, 10};
  int BLy[]= { 10, 10, 10, 10, 10, 10, 10, 10, 10,    -10,-10,-10,-10,-10,-10,-10,-10,-10};
  
  int FRz[]= { 40, 30, 20, 10,  0,-10,-20,-30,-40,    -40,-30,-20,-10,  0, 10, 20, 30, 40};
  int FLz[]= { 40, 30, 20, 10,  0,-10,-20,-30,-40,    -40,-30,-20,-10,  0, 10, 20, 30, 40};
  int BRz[]= { 40, 30, 20, 10,  0,-10,-20,-30,-40,    -40,-30,-20,-10,  0, 10, 20, 30, 40};
  int BLz[]= { 40, 30, 20, 10,  0,-10,-20,-30,-40,    -40,-30,-20,-10,  0, 10, 20, 30, 40};
  
  int lgTab = sizeof(FRx)/sizeof(int);
  int i=0, j=lgTab-1;  if(c=='R'){  i=-(lgTab-1); j=0; }
  for( i;i<=j;i++){
    IK(+FRx[abs(i)],FRy[abs(i)],-FRz[abs(i)],FRLS,FRRS,FRS);   // Front Right Leg
    IK(-FLx[abs(i)],FLy[abs(i)],+FLz[abs(i)],FLLS,FLRS,FLS);   // Front Left Leg
    IK(+BRx[abs(i)],BRy[abs(i)],+BRz[abs(i)],BRLS,BRRS,BRS);   // Back Right Leg
    IK(-BLx[abs(i)],BLy[abs(i)],-BLz[abs(i)],BLLS,BLRS,BLS);   // Back Left Leg
  }
}

void IK(int Px, int Py, int Pz, int LS, int RS, int SS){  // Inverse Kinematics function
  if (! digitalRead(pb)) resetFunc();
  int err;
  float Ax=0, Ay=120, Az=0, c=80; // Values of paw coordonates

  float dz=Ay-Py, ez=Az-Pz;                   // Z diagonal calculations
  float hz=sqrt((dz*dz)+(ez*ez));             //
  float D=acos(dz/hz);   if(ez<0)D=(-D);      //

        Ay=Ay*cos(D);                         // X Y diagonal calculations
        Az=Az*sin(D);                         //
  float d=Ay-Py, e=Ax-Px;                     //

  float h=sqrt((d*d)+(e*e));                  //
  float B=asin(d/h);    if(e<0)B=(PI-B);      // B is the top angle of the rectangle triangle
  float A=acos(h/(2*c));                      // A is the Diamond half top angle (cosin law)

  int S1=round(degrees(B-A))+Err[LS];         // S1 is the left servo angle in degrees +Err
  int S2=round(degrees(B+A))+Err[RS];         // S2 is the right servo angle in degrees +Err
  if (SS==FRS || SS==BLS) err=-Err[SS]; else err=Err[SS];
  int S3=round(degrees((PI/2)+D))+err;    // S3 is the shoulder servo angle in degrees +Err

//DEBUG
//  Serial.print(String()+"\n\n"+"\tTarget coordinates : Px="+Px+"  Py="+Py+"  Pz="+Pz+"\t\tLeg servos :   LS="+LS+"  RS="+RS+"  SS="+SS);
//  Serial.print(String()+"\n"+"\tInverse Kinematics values : D°= "+round(degrees(D))+"     B°= "+round(degrees(B))+"     A°= "+round(degrees(A)));
//  Serial.print(String()+"\n"+"\tServo angles results : S1= "+S1+"°\t\tS2= "+S2+"°\tS3= "+S3+"°");

// - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL -
  if (h>(c+c)){Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t h=");Serial.print(h);Serial.print(" > ");Serial.print(c+c);Serial.print(" is too long !!!!!");return;}
  if (S1<0)   {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S1=");Serial.print(S1);Serial.print(" <0° is not reachable !!!!!");return;}
  if (S1>95)  {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S1=");Serial.print(S1);Serial.print(" >95° is not reachable !!!!!");return;}
  if (S2>180) {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S2=");Serial.print(S2);Serial.print(" >180° is not reachable !!!!!");return;}
  if (S2<85)  {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S2=");Serial.print(S2);Serial.print(" <85° is not reachable !!!!!");return;}
  if (S3<45)  {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S3=");Serial.print(S3);Serial.print(" <45° is not reachable !!!!!");return;}
  if (S3>135) {Serial.print("\n\t Target : Px=");Serial.print(Px);Serial.print(" Py=");Serial.print(Py);Serial.print(" Pz=");Serial.print(Pz);Serial.print("\t angle S3=");Serial.print(S3);Serial.print(" >135° is not reachable !!!!!");return;}
// - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL - RESTRICTED AREA CONTROL -

// Servos activation
  if (OnOff[LS]) Srv[LS].writeMicroseconds(map(S1,0,180,Smin[LS],Smax[LS]));   // set target Left servo if servo switch is On
  if (OnOff[RS]) Srv[RS].writeMicroseconds(map(S2,0,180,Smin[RS],Smax[RS]));   // set target Right servo if servo switch is On
  if (OnOff[SS]) Srv[SS].writeMicroseconds(map(S3,0,180,Smin[SS],Smax[SS]));   // set target Shoulder servo if servo switch is On
  delayMicroseconds(Speed);                       // speed of action
}
