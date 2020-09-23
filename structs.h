typedef struct s_player {
    /*the users position*/
    double posX;
    double posY;
    /*the direction the user is watching*/
    int dirX;
    int dirY;
    /*camera plane of the map*/
    double planeX;
    double planeY;
    /*time of the current frame*/ 
    double time;
    /*time of the old frame*/
    double old_time;
    /*the x-coordinate of */
    /*rays X and Y*/
    double rayDirX;
    double rayDirY;
    


} t_player;

