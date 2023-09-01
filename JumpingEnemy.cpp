#include "JumpingEnemy.h"

void JumpingEnemy::jump_and_fall(){
    mv_left_right();

    if (!(this->isJumping) && !(this->isFalling)){
        this->isJumping = true;
        this->jumpCounter = this->jumpForce;
        jump();
    }
    else if (this->isJumping){
        jump();
    }
    else if (this->isFalling){
        fall();
    }
    
}