//wind_direction
//wind_velocity

//풍향(Wind direction)풍향은 바람이 불어오는 방향을 말하며, 보통 8방위, 더욱 상세하게는
//그 중간을 포함한 16방위로 나타낸다. 
#define DIR_N      0   // 정북 0
#define DIR_NNE   22.5 // 북북동 22.5
#define DIR_NE    45   // 북동 45
#define DIR_ENE   67.5 // 동북동 67.5
#define DIR_E     90   // 정동 90
#define DIR_ESE  112.5 // 동남동 112.5
#define DIR_SE   135   // 남동 135
#define DIR_SSE  157.5 // 남남동 157.5
#define DIR_S    180   // 정남 180
#define DIR_SSW  202.5 // 남남서 202.5
#define DIR_SW   225   // 남서 225
#define DIR_WSW  247.5 // 서남서 247.5
#define DIR_W    270   // 정서 270
#define DIR_WNW  292.5 // 서북서 292.5
#define DIR_NW   315   // 북서 315
#define DIR_NNW  337.5 // 북북서 337.5
#define UNKNOW_DIR -1  // 정온 풍속이 작아 풍향을 알수 없음

// Message to post
char message[128] = "";

int winVaneValue = 0;        
float windSpeed = 0;
float rainGauge = 0;
float windDirection = 0;
char windName[4];  // N (North)  S South,   NS(north south)   NNS(north north south)

int windVanePin = A0;
int windSpeedPin = 2;
int rainGaugePin = 3;

unsigned long windSpeedTimer;
int windSpeedState = true; 

int windSpeedCounter = 0;
unsigned long rainGaugeTimer;
int rainGaugeState = true; 
int rainGaugeCounter = 0;

void setup() {
  Serial.begin(9600);
  //wind speed sensor
  pinMode(windSpeedPin, INPUT);
  digitalWrite(windSpeedPin, HIGH);
  //rain gauge sensor
  pinMode(rainGaugePin, INPUT);
  digitalWrite(rainGaugePin, HIGH);
}

/*
* char 배열의 문자열정보를 Serial통해 문자로 전송 ,  PC에서 참고용
* char 배열을 사용한것은 차후 인터넷통신(트위터전송)을 위한 것입니다.
*/
void printChars(char *message, int len) {
  if(len == 0) return;
  for(int i=0; i<128; i++) { Serial.print(message[i]); }
  Serial.println();
}

/*
* f2h와 f2p는  float형의 정수부와 소수부를 위한 것입니다.
* sprintf에서 float형 사용에 문제가 있어서 땜빵으로 사용된 함수입니다.
*/
int f2h( float num){
  return int(num);
}

int f2p( float num){
  return (num - int(num)) * 100;
}


void loop() {
  windSpeedTimer = millis() + 1000; // 1초를 주기로 반복됩니다.
  windSpeedCounter = 0;
  while( millis() < windSpeedTimer ){
    delay(20); //20ms 주기로 센서의 스위칭을 감지합니다.
    //wind speed  풍속계 센서 감지부
    if( (windSpeedState == true ) && !digitalRead( windSpeedPin) ){ 
        windSpeedCounter++;     //스위치 상태가 high에서 low로 떨어지는 순간을 감지합니다.
        windSpeedState = false;
    }
    else if( (windSpeedState == false) && digitalRead(windSpeedPin) ){
        windSpeedState = true;
    }    
    //rain gauge
    if((rainGaugeState == true ) && !digitalRead( rainGaugePin) ) { 
        rainGaugeCounter++;     //스위치 상태가 high에서 low로 떨어지는 순간을 감지합니다.
        rainGaugeState = false;
    }
    else if( (rainGaugeState == false) && digitalRead(rainGaugePin) ){
      rainGaugeState = true;
    }        
  }
  rainGaugeTimer++;
  
  if(rainGaugeTimer > 360){// 10초 * 360 = 3600초(1시간)  지난 1시간동안 누적한 강수계 카운터로 강수량 계산
    rainGauge = rainGaugeCounter * 0.2794;
    rainGaugeCounter = 0; 
    rainGaugeTimer = 0;
  }
   
    windSpeed = windSpeedCounter * 0.24 ;   // 1초당 1회 스위칭시 2.4km/h 속력이며 10초 기간이므로 0.24가 됨
    getWindDirection();  // 풍향은 발표시점에 1회만 측정
    
    //char 배열에 정보를 취합(인터넷 전송에 적합한 자료형)
    /*
    sprintf(message, "Wind: %s/%d.%d, %d.%d(km/h) Rain %d.%d(mm/h).", 
      windName, f2h(windDirection), f2p(windDirection), f2h(windSpeed), f2p(windSpeed), f2h(rainGauge), f2p(rainGauge) 
    );
    */
    
    sprintf(message, "Wind: %s/%d.%d, %d.%d(km/h))",
      windName, f2h(windDirection), f2p(windDirection), f2h(windSpeed), f2p(windSpeed)
    );
    
    
// Format : WEATHER INFO [(DIR:ANGLE),(SPD),(RAIN)] (NNE:22.5),(0.24km/h),(4.18mm/h)
    //printChars( message, sizeof(message) ); //PC에서 참고용으로 시리얼전송
    Serial.print("WEATHER INFO (DEG,SPD,RAIN) (");
    Serial.print(windDirection);
//    Serial.print(":"); 
//    Serial.print(f2p(windDirection)); 
    Serial.print(","); 
    Serial.print(windSpeed); 
    Serial.print("km/h,"); 
//    Serial.print(message);
//    Serial.print(" Rain:[");
    Serial.print((float)rainGaugeCounter*0.2794);
    Serial.print("mm/h)\n");
    //이후 소개할 예제에서 위 자료를 이더넷을 통해 트위터에 포스팅하게됨  
}

/*
* 풍향측정: 아날로그핀입력되는 전압값으로 16가지 방향중 하나로 계산됨.
*/
float getWindDirection(void){
  int readValue = analogRead(windVanePin);            
  // 0~1023 사이의 입력값을 0~5V 기준 값으로 비례변경함.
  winVaneValue = map(readValue, 0, 1023, 0, 500);    
  //이제 winVaneValue는 데이타 시트정보상의 방위별 전압치와 유사한 값이 됩니다.
  
  if( winVaneValue < 35){ 
    //0~0.35V를 동동서 로 인식함
    //   112.5  0.32v (31 32)    0~35
    windDirection = DIR_ESE;
    strcpy(windName ,"ESE");        
  } 
  else if( winVaneValue < 43 ){
    //   67.5  0.41v(40 41)    ~42    
    windDirection = DIR_ENE;
    strcpy(windName , "ENE");        
  } 
  else if( winVaneValue < 50 ){
    //   90  0.45v(44 45)      ~50    
    windDirection = DIR_E;
    strcpy(windName , "E");        
  } 
  else if( winVaneValue < 70 ){
    //   157.5  0.62v(60 62)   ~70
    windDirection = DIR_SSE;
    strcpy(windName , "SSE");        
  } 
  else if( winVaneValue < 100 ){
    //   135  0.90v(89 90)      ~100
    windDirection = DIR_SE;  
    strcpy(windName , "SE");        
  } 
  else if( winVaneValue < 130 ){
    //   202.5  1.19v(119 120)  ~130
    windDirection = DIR_SSW;  
    strcpy(windName , "SSW");        
  } 
  else if( winVaneValue < 170 ){
    //   180  1.40v(140 141)   ~170
    windDirection = DIR_S;  
    strcpy(windName , "S");        
  } 
  else if( winVaneValue < 210 ){
    //   22.5  1.98v(198 199)  ~210
    windDirection = DIR_NNE;  
    strcpy(windName , "NNE");            
  } 
  else if( winVaneValue < 250 ){
    //   45  2.25v(226 227)    ~250
    windDirection = DIR_NE;  
    strcpy(windName , "NE");            
  } 
  else if( winVaneValue < 300 ){
    //  247.5  2.93v(293 294)  ~300
    windDirection = DIR_WSW;  
    strcpy(windName , "WSW");        
  } 
  else if( winVaneValue < 320 ){
    //  225  3.08v(308 310)   ~320
    windDirection = DIR_SW;  
    strcpy(windName , "SW");        
  } 
  else if( winVaneValue < 360 ){
    //  337.5  3.43 (343 345)  ~360
    windDirection = DIR_NNW;  
    strcpy(windName , "NNW");        
  } 
  else if( winVaneValue < 395 ){
    //   0  3.84v(384~385)    ~395
    windDirection = DIR_N;  
    strcpy(windName , "N");
  } 
  else if( winVaneValue < 415 ){
    //  292.5  4.04v(405 406)  ~415
    windDirection = DIR_WNW;  
    strcpy(windName , "WNW");    
  } 
  else if( winVaneValue < 450 ){
    //  315  4.34(433 434)  ~450
    windDirection = DIR_NW;  
    strcpy(windName , "NW");        
  } 
  else if( winVaneValue < 490 ){
    //  270  4.62v(461 463)    ~490
    windDirection = DIR_W;  
    strcpy(windName , "W");        
  } 
  else{
   //error 
  }
}


