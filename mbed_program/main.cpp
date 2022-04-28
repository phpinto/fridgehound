#include "mbed.h"
#include "uLCD_4DGL.h"
 
uLCD_4DGL uLCD(p9, p10, p11); // serial tx, serial rx, reset pin;
AnalogIn sensor(p15);
DigitalIn pbUp(p8);
DigitalIn pbLeft(p29);
DigitalIn pbDown(p28);
DigitalIn pbRight(p24);
DigitalIn pbSelect(p20);
DigitalIn pbBackToMenu(p19);
AnalogIn LM61(p18);
Serial pc(USBTX, USBRX);
 
int main()
{
 
    pbUp.mode(PullUp);
    pbLeft.mode(PullUp);
    pbDown.mode(PullUp);
    pbRight.mode(PullUp);
    pbSelect.mode(PullUp);
    pbBackToMenu.mode(PullUp);
 
    int phase = 0;
    int option = 1;
    bool image_change = true;
    int daysRemaining = -1;
    int timer = 0;
    bool foodStored = false;
    float tempC, tempF;
    float sensorData = 0.0;
    int foodType = 9;
    int counter = 0;
 
    uLCD.media_init();
    uLCD.set_sector_address(0x003B, 0x8000);
    uLCD.display_image(0, 0);
    wait(3.0);
    phase = 1;
 
    while (1) {
 
        sensorData = sensor.read();
        //Logic that reduces the timer variable every second.
        switch (phase) {
 
        //Phase 1: Main Menu
        case 1:
            switch (option) {
            case 0: //Reset food option selected
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x81C7);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                //Load main menu select reset food
                if (pbSelect == 0) { //Selected this option
                    phase = 2;
                    image_change = true;
                }
                break;
            case 1: //Add food option selected
                //Load main menu add food
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8208);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    phase = 3; //Move to food addition phase
                    option = 0;
                    image_change = true;
                }
                break;
            case 2: //Check status option selected
                //Load main menu check status
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8186);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    phase = 5;
                    image_change = true;
                }
            }
            if (pbRight == 0) { //press right button
                option += 1;
                option = option % 3;
                image_change = true;
            }
            if (pbLeft == 0) { //press left button
                option -= 1;
                image_change = true;
                if (option < 0) {
                    option = 2;
                }
            }
 
            //More things happen in the main menu
            break;
 
        //Phase 2: Food Reset Stage
        case 2:
            //Load "food was reset" image
            uLCD.media_init();
            uLCD.set_sector_address(0x003B, 0x89A6);
            uLCD.display_image(0, 0);
            wait(3.0);
            phase = 1;
            option = 0;
            foodStored = false;
            daysRemaining = -1;
            foodType = 9;
            break;
 
        //Phase 3: Food Addition Stage
        case 3:
            switch (option) {
            case 0: //Load first option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8820);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 0;
                }
                break;
            case 1: //Load second option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x875D);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 1;
                }
                break;
            case 2: //Load third option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8965);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 2;
                }
                break;
            case 3: //Load fourth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8924);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 3;
                }
                break;
            case 4: //Load fifth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x879E);
                    uLCD.display_image(0, 0);
                    image_change = true;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 4;
                }
                break;
 
            case 5: //Load sixth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8861);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 5;
                }
                break;
             case 6: //Load sixth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x88A2);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 6;
                }
                break;
            case 7: //Load sixth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x88E3);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 7;
                }
                break;
            case 8: //Load sixth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x87DF);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                if (pbSelect == 0) {
                    option = 0; //Here we will put the number of days expected for this type of food
                    phase = 4;
                    image_change = true;
                    foodType = 8;
                }
                break;
            }
 
            if (pbDown == 0) {
                option++;
                option = option % 9;
                image_change = true;
            }
 
            if (pbUp == 0) {
                image_change = true;
                if (option == 0) {
                    option = 8;
                }
                else {
                    option--;
                }
            }
 
            if (pbSelect == 0) {
                phase = 4;
                option = 0;
                image_change = true;
            }
            break;
 
        //Phase 4: Food Timing Section
        case 4:
            switch (option) {
            case 0: //Load first option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8249);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 1: //Load second option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x828A);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 2: //Load third option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x82CB);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 3: //Load fourth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x830C);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 4: //Load fifth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x834D);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 5: //Load sixth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x838E);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 6: //Load seventh option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x83CF);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 7: //Load eighth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8410);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 8: //Load ninth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8451);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 9: //Load tenth option
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8492);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            }
                        if (pbDown == 0) {
                            option++;
                            option = option % 10;
                            image_change = true;
                        }
 
                        if (pbUp == 0) {
                            image_change = true;
                            if (option == 0) {
                                option = 9;
                            }
                            else {
                                option--;
                            }
                        }
 
                            if (pbSelect == 0) { //Food was added
                                image_change = true;
                                foodStored = true;
                                daysRemaining = option + 1;
                                timer = daysRemaining * 3600 * 24;
                                phase = 5;
                            }
            break;
 
        //Phase 5: Food Status Section
        case 5:
            switch (daysRemaining) {
            case -1: //Load no food stored
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8082);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 0: //Load "food is no good" image
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8041);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 1: //Load 1 day remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x84D3);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 2: //Load 2 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8514);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 3: //Load 3 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8555);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 4: //Load 4 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8596);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 5: //Load 5 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x85D7);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 6: //Load 6 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8618);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 7: //Load 7 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8659);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 8: //Load 8 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x869A);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 9: //Load 9 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x86DB);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            case 10: //Load 10 days remaining.
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x871C);
                    uLCD.display_image(0, 0);
                    image_change = false;
                }
                break;
            }
 
            if (pbRight == 0) { //Press Right
                phase = 6;
                image_change = true;
            }
 
            if (pbBackToMenu == 0) { //Press Menu Button
                phase = 1;
                option = 1;
                image_change = true;
            }
 
            break;
 
        //Phase 6: Sensor Data
        case 6:
        if(daysRemaining != -1){
            if (sensorData < 0.33) {
                    //Display food is good
                    if(image_change == true){
                        uLCD.media_init();
                        uLCD.set_sector_address(0x003B, 0x8145);
                        uLCD.display_image(0, 0);
                        //image_change = false;
                    }
                }
                else if (sensorData < 0.66) {
                    //Display food is medium
                    if(image_change == true){
                        uLCD.media_init();
                        uLCD.set_sector_address(0x003B, 0x80C3);
                        uLCD.display_image(0, 0);
                        //image_change = false;
                    }
                }
                else {
                    //Display food is bad
                    if(image_change == true){
                        uLCD.media_init();
                        uLCD.set_sector_address(0x003B, 0x8041);
                        uLCD.display_image(0, 0);
                        //image_change = false;
                    }
                }
            }
            else{
                if(image_change == true){
                    uLCD.media_init();
                    uLCD.set_sector_address(0x003B, 0x8104);
                    uLCD.display_image(0, 0);
                    //image_change = false;
                }
            }
 
            if (pbLeft == 0) { //Press Left
                phase = 5;
                image_change = true;
            }
 
            break;
        }
        if (pbBackToMenu == 0) { //Press Menu Button
            phase = 1;
            option = 1;
            image_change = true;
       }
       tempC = ((LM61*3.3)-0.600)*100.0;
       //convert to degrees F
       tempF = (9.0*tempC)/5.0 + 32.0;
       tempF = tempF;
       if (tempF >= 100){
           tempF = 99.99;
           }
       counter++;
       if((counter % 10000) == 0){
           int days = daysRemaining;
           if(days == -1){
               days = 0;
               }
           pc.printf("%i %.2f %.2f %i",foodType,sensorData,tempF,days);
           }
       
    }
}