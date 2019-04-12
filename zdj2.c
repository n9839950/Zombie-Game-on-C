
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <curses.h>


#define DELAY (25)

#define HERO_WIDTH (3)
#define HERO_HEIGHT (3)
#define ZOMBIE_WIDTH (4)
#define ZOMBIE_HEIGHT (4)
#define PLAT_W (40)
#define PLAT_H (1)
#define door_width (4)
#define door_height (4)
#define PLAT2_W (12)
#define PLAT2_H (1)
#define MONSTER_W (3)
#define MONSTER_H (2)
#define tresure_W (3)
#define treasure_H (2)
#define PLAT4_W (48)
#define PLAT4_H (1)
#define PLAT3_W (48)
#define PLAT3_H (1)

int level = 1 ;
int minutes = 0 ;
int seconds = 0;
int score = 0 ;
int lives = 10;
int set_time ;

bool game_over = false;
bool update_screen = true;

// character introduction
char * hero_image =
/**/  " o "
/**/  "/|\\"
/**/  "/ \\" ;

char * zombie_image =
/**/  "ZZZZ"
/**/  "  Z "
/**/  " Z  "
/**/  "ZZZZ";


char * platform_img = "==============================================================";

char * door_img =
/**/    "EXIT"
/**/    "|  |"
/**/    "| .|"
/**/    "|  |" ;

char * msg_image =
/**/    "          Goodbye and thank-you for playing.    "
/**/    "            Press any key to exit...            "
/**/    "            your total score is                ";


char * platform2_img = "===================";


char * platform3_img = "=========================================================================================";

char * platform4_img = "==========================================================================================";


char * monster_img = 
/**/  "\\ /"
/**/  " | ";

char * treasure_img =   
/**/  "   "
/**/  " $ ";




sprite_id hero;

sprite_id zombie;

sprite_id platform;

sprite_id door;

sprite_id platform2;

sprite_id monster ;

sprite_id treasure;

sprite_id platform4;

sprite_id platform3;


 
void display_hud() {
    draw_formatted(0,0, "Times: %.2d:%.2d", minutes, seconds );
    draw_formatted(screen_width()/4,0,"Lives: %d", lives);
    draw_formatted(screen_width()/2,0,"Level: %d", level);
    draw_formatted(screen_width()*3/4,0, "Score: %d",score);
    show_screen();
}



void setup(void) {
    
    int w = screen_width(), h = screen_height();
    
    
    int left = 1 ;
    int top = 1;
    int right = w  ;
    int bottom = h - 1  ;
    draw_line (left - 1 , top , left , bottom   , '|') ;
    draw_line (right - 1 ,top , right ,bottom  , '|') ;
    draw_line ( left - 1   , bottom  , right , bottom   , '=');
    draw_line (left - 1 , top  ,right ,top , '~');
    
    // hero loaction
    hero = sprite_create(3 ,screen_height() - 4 ,HERO_WIDTH , HERO_HEIGHT , hero_image);
    sprite_draw (hero);
    
    
    
    // plateform location
    platform = sprite_create( screen_width()/3 , screen_height() - 1 - 10.5 , round(screen_width()/3) , PLAT_H, platform_img);
    sprite_draw(platform);


    door = sprite_create ( w - 9 , h - 5 , door_width , door_height , door_img );
    sprite_draw(door);







   
  if (level == 1){
    
    // zombie location
    zombie = sprite_create( w - 9 , h - 5 , ZOMBIE_WIDTH, ZOMBIE_HEIGHT, zombie_image );
    sprite_draw(zombie);
    
    
    //int angle = rand() % 180;
    sprite_turn_to( zombie, -0.4, 0 );
    //sprite_turn( zombie, angle );
    }
    
    //exit location
   
    show_screen();
    
    



if (level == 2) {



    platform2 = sprite_create( screen_width() - 66, screen_height() - 1 - 21 , PLAT2_W , PLAT2_H , platform2_img);
    sprite_draw(platform2);

     

      monster = sprite_create( w - 15, h - 4 , MONSTER_W, MONSTER_H, monster_img );
    sprite_draw(monster);
    sprite_turn_to (monster , -0.5 , 0);



    

    treasure = sprite_create( w - 62 , h - 31 , tresure_W , treasure_H , treasure_img);
    sprite_draw (treasure);
    
    
    show_screen();


}

if(level == 3) {



   platform3 = sprite_create( screen_width()/3 , screen_height() - 1 - 10.5 , round(screen_width()/3) , PLAT3_H, platform3_img);
    sprite_draw(platform3);

    sprite_turn_to(platform3, 0.4 , 0 );



   platform4 = sprite_create( screen_width()/3 , screen_height() - 21 , round(screen_width()/3) , PLAT4_H, platform4_img);
    sprite_draw(platform4);

    sprite_turn_to(platform4, -0.4 , 0 );
  
  
    
    treasure = sprite_create( w - 62 , h - 31 , tresure_W , treasure_H , treasure_img);
    sprite_draw (treasure);

    show_screen();
}


}  



void process_collison (sprite_id who_moved)

{
    
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
    
    int px = round(sprite_x(platform));
    int py = round (sprite_y(platform));
    
    
    
    bool collided = true;
    
    if (px >= hx + HERO_WIDTH) collided = false ;
    if (py >= hy + HERO_HEIGHT) collided = false ;
    if (hx >= px + PLAT_W) collided = false ;
    if (hy >= py + PLAT_H) collided = false ;
    
    
    if (collided) {
        
        
        if (who_moved == hero ) {
            
            double dx = sprite_dx(hero), dy = sprite_dy(hero);
            
            if (hy == py + PLAT_H - 2 && dy < 0) {
                dy = -dy;
            }
            
            else if (hx + HERO_WIDTH == px && dx > 0) {
                dx = 0 ;
                
            }
            
            else if (hx == px + PLAT_W  && dx < 0){
                dx = 0 ;
                
            }
            
            else {
                dy = 0 ;
                
                
            }
            
            hero->dx = 0;
            
            
            sprite_back (hero);
            sprite_turn_to (hero , dx , dy);
        }
        
        else {
            
            sprite_move_to (hero , sprite_x(hero) , sprite_y(platform) + PLAT_H );
        }
        
    }
    
    
}

bool process_collison3 (sprite_id who_moved)

{
    
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
    
    int ax = round(sprite_x(platform3));
    int ay = round (sprite_y(platform3));
    
    
    
    bool collided = true;
    
    if (ax >= hx + HERO_WIDTH) collided = false ;
    if (ay >= hy + HERO_HEIGHT) collided = false ;
    if (hx >= ax + PLAT3_W) collided = false ;
    if (hy >= ay + PLAT3_H) collided = false ;
    
    
    if (collided) {
        
        
        if (who_moved == hero ) {
            
            double dx = sprite_dx(hero), dy = sprite_dy(hero);
            
            if (hy == ay + PLAT3_H - 1 && dy < 0) {
                collided = false ;
                dy = -dy;
            }
            
            else if (hx + HERO_WIDTH - 1 == ax && dx > 0) {
                dx = 0 ;
                collided = false ;
            }
            
            else if (hx == ax + PLAT3_W - 1 && dx < 0){
                dx = 0 ;
                collided = false ;
            }
            
            else {
                dy = 0 ;
                
                
            }
            
            hero->dx = 0;
            
            
            sprite_back (hero);
            sprite_turn_to (hero , dx , dy);
        }
        
        else {
            
            sprite_move_to (hero , sprite_x(hero) , sprite_y(platform3) + PLAT3_H );
        }
        
    }
    
    return collided ;
}


bool process_collison4 (sprite_id who_moved)

{
    
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
    
    int ix = round(sprite_x(platform4));
    int iy = round (sprite_y(platform4));
    
    
    
    bool collided = true;
    
    if (ix >= hx + HERO_WIDTH) collided = false ;
    if (iy >= hy + HERO_HEIGHT) collided = false ;
    if (hx >= ix + PLAT4_W) collided = false ;
    if (hy >= iy + PLAT4_H) collided = false ;
    
    
    if (collided) {
        
        
        if (who_moved == hero ) {
            
            double dx = sprite_dx(hero), dy = sprite_dy(hero);
            
            if (hy == iy + PLAT4_H - 1 && dy < 0) {
                collided = false ;
                dy = -dy;
            }
            
            else if (hx + HERO_WIDTH - 1 == ix && dx > 0) {
                dx = 0 ;
                collided = false ;
            }
            
            else if (hx == ix + PLAT4_W - 1 && dx < 0){
                dx = 0 ;
                collided = false ;
            }
            
            else {
                dy = 0 ;
                
                
            }
            
            hero->dx = 0;
            
            
            sprite_back (hero);
            sprite_turn_to (hero , dx , dy);
        }
        
        else {
            
            sprite_move_to (hero , sprite_x(hero) , sprite_y(platform4) + PLAT4_H );
        }
        
    }
    
    return collided ;
}

void platform3_move(){
    int px = round(sprite_x(platform3)) ;

  if(px < 2 ) {
    sprite_turn_to (platform3 , 0.4 , 0);
  }

  if (px > screen_width() - PLAT3_W) 
  {
    sprite_turn_to (platform3 , -0.4 , 0);
  }

  sprite_step(platform3);
  sprite_draw(platform3);
}

void platform4_move (){

    int wx = round(sprite_x(platform4));

  if (wx < 2 ) {
    sprite_turn_to (platform4 , 0.4 , 0) ;

  }

  if (wx > screen_width() - PLAT4_W)
  {
    sprite_turn_to(platform4 , -0.4 ,0);
  }

  sprite_step(platform4);
  sprite_draw(platform4);
}

void collision2 (sprite_id who_moved)

{
    
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
    
    int qx = round(sprite_x(platform2));
    int qy = round (sprite_y(platform2));
    
    
    
    bool collided = true;
    
    if (qx >= hx + HERO_WIDTH) collided = false ;
    if (qy >= hy + HERO_HEIGHT) collided = false ;
    if (hx >= qx + PLAT2_W) collided = false ;
    if (hy >= qy + PLAT2_H) collided = false ;
    
    
    if (collided) {
        
        
        if (who_moved == hero ) {
            
            double dx = sprite_dx(hero), dy = sprite_dy(hero);
            
            if (hy == qy + PLAT2_H - 2 && dy < 0) {
                dy = -dy;
            }
            
            else if (hx + HERO_WIDTH == qx && dx > 0) {
                dx = 0 ;
                
            }
            
            else if (hx == qx + PLAT2_W  && dx < 0){
                dx = 0 ;
                
            }
            
            else {
                dy = 0 ;
                
                
            }
            
            hero->dx = 0;
            
            
            sprite_back (hero);
            sprite_turn_to (hero , dx , dy);
        }
        
        else {
            
            sprite_move_to (hero , sprite_x(hero) , sprite_y(platform2) + PLAT2_H );
        }
        
    }
    
    
}

bool collisionmosture() {
  bool collided = true;
  
  int hx = round(sprite_x(hero));
  int hy = round(sprite_y(hero));
  int hr = hx + HERO_WIDTH - 1;
  int hb = hy + HERO_HEIGHT - 1;
  
  int mx = round(sprite_x(monster));
  int my = round(sprite_y(monster));
  int mr = mx + MONSTER_W - 1;
  int mb = my + MONSTER_H - 1;
  
  if (hr < mx ) { collided = false; }
  else if (hb < my ) { collided = false; }
  
  else if (mr < hx ) { collided = false; }
    else if (mb < hy ) { collided = false; }
  
  return collided;
}

bool collisiontreasure() {
  bool collided = true;
  
  int hx = round(sprite_x(hero));
  int hy = round(sprite_y(hero));
  int hr = hx + HERO_WIDTH - 1;
  int hb = hy + HERO_HEIGHT - 1;
  
  int tx = round(sprite_x(treasure));
  int ty = round(sprite_y(treasure));
  int tr = tx + tresure_W - 1;
  int tb = ty + treasure_H - 1;
  
  if (hr < tx ) { collided = false; }
  else if (hb < ty ) { collided = false; }
  
  else if (tr < hx ) { collided = false; }
    else if (tb < hy ) { collided = false; }
  
  return collided;
}





bool collision() {
    bool collided = true;
    
    int hx = round(sprite_x(hero));
    int hy = round(sprite_y(hero));
    int hr = hx + HERO_WIDTH - 1;
    int hb = hy + HERO_HEIGHT - 1;
    
    int zx = round(sprite_x(zombie));
    int zy = round(sprite_y(zombie));
    int zr = zx + ZOMBIE_WIDTH - 1;
    int zb = zy + ZOMBIE_HEIGHT - 1;
    
    if (hr < zx ) { collided = false; }
    if (hb < zy ) { collided = false; }
    
    if (zr < hx ) { collided = false; }
    if (zb < hy ) { collided = false; }
    
    return collided;
}

bool collision1() {
  bool collided = true;
  
  int hx = round(sprite_x(hero));
  int hy = round(sprite_y(hero));
  int hr = hx + HERO_WIDTH - 1;
  int hb = hy + HERO_HEIGHT - 1;
  
  int ex = round(sprite_x(door));
  int ey = round(sprite_y(door));
  int er = ex + door_width - 1;
  int eb = ey + door_height - 1;
  
  if (hr < ex ) { collided = false; }
  else if (hb < ey ) { collided = false; }
  
  else if (er < hx ) { collided = false; }
    else if (eb < hy ) { collided = false; }
  
  return collided;
}
     

     bool collisionmons() {
  bool collided = true;
  
  int hx = round(sprite_x(hero));
  int hy = round(sprite_y(hero));
  int hr = hx + HERO_WIDTH - 1;
  int hb = hy + HERO_HEIGHT - 1;
  
  int mx = round(sprite_x(monster));
  int my = round(sprite_y(monster));
  int mr = mx + MONSTER_W - 1;
  int mb = my + MONSTER_H - 1;
  
  if (hr < mx ) { collided = false; }
  else if (hb < my ) { collided = false; }
  
  else if (mr < hx ) { collided = false; }
    else if (mb < hy ) { collided = false; }
  
  return collided;
}



void monster_move( ){


   
    double mx = sprite_x(monster) ;

    if (mx < 2){
        
        sprite_turn_to(monster, 0.5,0);
    }
    
    if ( mx > screen_width() - 3 - ZOMBIE_WIDTH)
    {
        sprite_turn_to(monster , -0.5 ,0);
    }


    
     sprite_step(monster);

    
    sprite_draw(monster);

     }

void zombie_move( ){    
 int zx = round(sprite_x(zombie));
    
    if (zx < 2){
        
        sprite_turn_to(zombie, 0.4,0);
    }
    
    if ( zx > screen_width() - 3 - ZOMBIE_WIDTH)
    {
        sprite_turn_to(zombie , -0.4 ,0);
    }
    
    
     sprite_step(zombie);

    
    sprite_draw(zombie);
}




void set_lvl2(void) {


         if (level == 2) {

            clear_screen();

            setup();

            update_screen = true ;

            sprite_move_to( zombie  , 50000, 200000);

            
   int  w = screen_width() , h = screen_height() ;

    platform2 = sprite_create( screen_width() - 66, screen_height() - 1 - 21 , PLAT2_W , PLAT2_H , platform2_img);
    sprite_draw(platform2);


     monster = sprite_create( w - 15, h - 4 , MONSTER_W, MONSTER_H, monster_img );
    sprite_draw(monster);
    sprite_turn_to (monster , -0.5 , 0);



    treasure = sprite_create( w - 62 , h - 31 , tresure_W , treasure_H , treasure_img);
    sprite_draw (treasure);
    

    //monster move 

   monster_move();


   
     
        
   // treasure
    draw_char( screen_width() - 60, screen_height() - 31, '$');
   
   

     show_screen();

         
}

}

void set_lvl3() {


         if (level == 3) {

            clear_screen();

            setup();

            update_screen = true ;

            sprite_move_to( monster  , 50000, 20000);

            
   int  w = screen_width() , h = screen_height() ;

   
   platform3 = sprite_create( screen_width()/3 , screen_height() - 1 - 10.5 , round(screen_width()/3) , PLAT3_H, platform3_img);
    sprite_draw(platform3);

    sprite_turn_to(platform3, 0.4 , 0 );



   platform4 = sprite_create( screen_width()/3 , screen_height() - 21 , round(screen_width()/3) , PLAT4_H, platform4_img);
    sprite_draw(platform4);

    sprite_turn_to(platform4, -0.4 , 0 );


    treasure = sprite_create( w - 62 , h - 31 , tresure_W , treasure_H , treasure_img);
    sprite_draw (treasure);
    


}
}
 

void process() {

if (lives == 0) {
    
     clear_screen();
     draw_formatted(screen_width()/4,(screen_height()/2)-1,"Goodbye and thank-you for game      ");
      draw_formatted(screen_width()/4,(screen_height()/2), "      Press any key to exit       ");
      draw_formatted(screen_width()/4,(screen_height()/2)+1,"       your total  score is %d "    , score);
      show_screen();
    game_over = true;
      wait_char();
 }


  int w = screen_width () , h = screen_height();
    
    double dx = sprite_dx(hero);
    double dy = sprite_dy(hero);

    double x = sprite_x(hero);
    double y = sprite_y(hero);

    int key = get_char();


    if(x < 1) {
        dx = 0 ;
        x = 1;
    }
    
    if (x > w - 1 - HERO_WIDTH) {
        dx = 0;
        x = w - 1 - HERO_WIDTH ;
    }    

    if (y < 2 ) {
        dy = 0 ;
        y = 2;
    }
    if ( y > h - 1 - HERO_HEIGHT){
        dy = 0 ;
        y = h - 1 - HERO_HEIGHT;

    }

    sprite_turn_to (hero, dx , dy ) ;
    sprite_move_to(hero , x , y );
    //hero gravity movement

    if ( key == KEY_LEFT && dy == 0 )
    {
        dx = dx - 0.15;
    }
    
    if (key == KEY_RIGHT && dy == 0 )
    {
        dx = dx + 0.15;
    }
   
     if (key == KEY_UP && dy == 0)
     {
        dy = dy - 1.3 ;
     }
        
     dy = dy + 0.1 ;

     sprite_turn_to (hero , dx , dy) ;
     sprite_step(hero) ;
    
    // zombie     
    

    process_collison(hero);





    
    if (level == 1){
     zombie_move();

      if ( collision() ) {
        
        lives -=  1 ;
        setup();
        
            if (lives == 0) {
    
     clear_screen();
     draw_formatted(screen_width()/4,(screen_height()/2)-1,"Goodbye and thank-you for game      ");
      draw_formatted(screen_width()/4,(screen_height()/2), "      Press any key to exit       ");
      draw_formatted(screen_width()/4,(screen_height()/2)+1,"       your total  score is %d "    , score);
      show_screen();
    game_over = true;
      wait_char();
 

        }
    }
}


    
 
    if (collision1()) {

       score += 100 ;
        level ++ ;
        clear_screen();
        set_lvl2();
        set_lvl3();



       
         }


      
         if (level == 2 ) {

     sprite_draw(platform2);

     sprite_draw(monster);
  
    // monster_move();
     monster_move();

     if (collisionmons()) {
        lives -= 1 ;

        setup();

     }

        if(collisiontreasure()) {

        sprite_hide(treasure) ;
        score = 150; 
     
    }

    if (collisionmosture()){

        lives -= 1;
        setup();
        if (score >= 150)
          sprite_hide(treasure);

    }

    if (level == 3) {

       process_collison3(hero);
       process_collison4(hero);

       sprite_draw(platform3);
       sprite_draw(platform4);

       if(collisiontreasure()) {

        sprite_hide(treasure) ;
        score += 50; 

        if (collision1 ()) {

            game_over = true ;
           
      clear_screen();
     draw_formatted(screen_width()/4,(screen_height()/2)-1,"Goodbye and thank-you for game      ");
      draw_formatted(screen_width()/4,(screen_height()/2), "      Press any key to exit       ");
      draw_formatted(screen_width()/4,(screen_height()/2)+1,"       your total  score is %d "    , score);
      show_screen();
      game_over = true;
      wait_char();
        }
     
    }

    } 

   xq

  //  draw_char( screen_width() - 60, screen_height() - 31, '$');
    
}
    
        

    if(key == 'l' && level < 5 ){
        
       process();
       set_lvl2();
       set_lvl3();
      
           level ++;
      
        }
     

    clear_screen();
    
    int left = 1 ;
    int top = 1;
    int right = w  ;
    int bottom = h - 1  ;
    draw_line (left - 1 , top , left , bottom   , '|') ;
    draw_line (right - 1 ,top , right ,bottom  , '|') ;
    draw_line ( left - 1   , bottom  , right , bottom  , '=');
    draw_line (left - 1 , top  ,right ,top , '~');
    
    draw_formatted(0,0, "Times: %.2d:%.2d", minutes, seconds );
    draw_formatted(screen_width()/4,0,"Lives: %d", lives);
    draw_formatted(screen_width()/2,0,"Level: %d", level);
    draw_formatted(screen_width()*3/4,0, "Score: %d",score);
    
    
    
    sprite_step(hero);
    
    process_collison(hero);
    // process_collison1(hero);


    
    sprite_draw( hero );
    sprite_draw( zombie ); 
    sprite_draw( platform);

    sprite_draw (door);

    
if (level == 2 ) {

     sprite_draw(platform2);

     sprite_draw(monster);
  
    // monster_move();
     monster_move();

     
     collision2(hero);

  
    sprite_draw(treasure);
}
    
    


  if (level == 3 ) {

     sprite_draw(platform3);

     sprite_draw(platform4);
  
    // monster_move();
     platform3_move();
     platform4_move();


     
     process_collison3(hero);
     process_collison4(hero);

  
    sprite_draw(treasure);

    if (collision1()) 
    {
        clear_screen();
     draw_formatted(screen_width()/4,(screen_height()/2)-1,"Goodbye and thank-you for playing game      ");
      draw_formatted(screen_width()/4,(screen_height()/2), "      Press any key to exit       ");
      draw_formatted(screen_width()/4,(screen_height()/2)+1,"       your total  score is %d "    , score);
      show_screen();
      game_over = true;
      wait_char();
    }
}
    
    
    show_screen();
    
    }



void time_update(){
    
    int current_time = get_current_time();
    if(current_time > set_time ){
        seconds++;
        set_time=current_time;
    }
    if (seconds == 60){
        minutes++;
        seconds=0;
    }
}



void cleanup (void){
    
}


int main(void) {
    setup_screen();
    setup();

    show_screen();
    
    while ( !game_over) {

        clear_screen();
        time_update();
        process();


       // level1(); 
        timer_pause(DELAY);
        
    }
    cleanup();
    
    return 0;
}
