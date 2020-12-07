class ROV
{
    public:
        vector<double> pos;
        vector<pair<double, double>> limitPos;
        vector<double> rotation;
        vector<double> facing;
        vector<double> acceleration;
        vector<double> speed;
        vector<bool> isMoving;
        double maxSpeed, bladeAngle, armLength;
        pair<double, double> limitArmLength;
        bool grasping;
        vector<vector<double>> colors;

        ROV(): pos( { 20.0, 25.0, 20.0 } ),
               limitPos( {{ -900.0, 900.0 }, 
                          { 25.0, 400.0 },
                          { -900.0, 900.0 }} ),
               rotation( { 0.0, 0.0, 1.0, 0.0 } ),
               facing( { 0.0, 0.0, 1.0 } ),
               acceleration( { 0.0, 0.0, 0.0 } ),
               speed( { 0.0, 0.0, 0.0 } ),
               isMoving( { false, false, false } ),
               maxSpeed( 2.0 ),
               bladeAngle( 0.0 ),
               armLength( 1.0 ),
               limitArmLength( { 1.0, 200.0 } ),
               grasping( false )
        { 
            colors = 
            { 
                { 0.0, 0.0, 0.0 },
                { 1.0, 1.0, 1.0 },
                { 0.3, 0.3, 0.3 },
                { 0.5, 0.5, 0.5 },
                { 0.6, 0.6, 0.6 },
                { 0.1, 0.5, 0.7 }
            };
        }

        void drawROV();
        void drawMainBody();
        void drawCamera();
        void drawPropeller( bool );
        void drawBlades();
        void drawArm();

        void boundAcc();
        void boundSpeed();
        void boundPos();
        void boundBladeAngle();
        void boundArmLength();
        void speedUpDown( bool );
        void moving();

        void turnLeftRight( bool );
        void setFacing();
};

void ROV::drawROV()
{
    glColor3f( 1.0, 1.0, 1.0 );

    glPushMatrix();
        glTranslatef( pos[0] + 20 * facing[0] + 22.071 * facing[2], pos[1] + 15, pos[2] + 20 * facing[2] - 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] + 20 * facing[0] - 22.071 * facing[2], pos[1] + 15, pos[2] + 20 * facing[2] + 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] - 20 * facing[0] + 22.071 * facing[2], pos[1] + 15, pos[2] - 20 * facing[2] - 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] - 20 * facing[0] - 22.071 * facing[2], pos[1] + 15, pos[2] - 20 * facing[2] + 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef( pos[0] + 20 * facing[0] + 22.071 * facing[2], pos[1] - 12, pos[2] + 20 * facing[2] - 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] + 20 * facing[0] - 22.071 * facing[2], pos[1] - 12, pos[2] + 20 * facing[2] + 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] - 20 * facing[0] + 22.071 * facing[2], pos[1] - 12, pos[2] - 20 * facing[2] - 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();
    glPushMatrix();
        glTranslatef( pos[0] - 20 * facing[0] - 22.071 * facing[2], pos[1] - 12, pos[2] - 20 * facing[2] + 22.071 * facing[0] );
        glutSolidCube( 1.0 );
    glPopMatrix();

    glPushMatrix();
        glTranslatef( pos[0], pos[1], pos[2] );
        glRotatef( rotation[0], rotation[1], rotation[2], rotation[3] );

        drawMainBody();
        drawCamera();
        drawPropeller( true );
        drawPropeller( false );
        drawArm();
        
    glPopMatrix();
}

void ROV::drawMainBody()
{
    glPushMatrix();
        glColor3f( colors[2][0], colors[2][1], colors[2][2] );
        glScalef( 20.0, 20.0, 40.0 );
        glutSolidCube( 1.0 );
    glPopMatrix();
}

void ROV::drawCamera()
{
    glPushMatrix();
        glTranslatef( 0.0, 10.0, 20.0 );

        glPushMatrix();
            glColor3f( colors[4][0], colors[4][1], colors[4][2] );
            glScalef( 10.0, 5.0, 5.0);
            drawTrapezoidalCube();
        glPopMatrix();

        glPushMatrix();
            glColor3f( colors[0][0], colors[0][1], colors[0][2] );
            glTranslatef( 0.0, 2.5, 0.25 );
            gluDisk( circleObj, 0.0, 1.5, 12, 1 );
        glPopMatrix();

        glPushMatrix();
            glColor3f( colors[1][0], colors[1][1], colors[1][2] );
            glTranslatef( 0.0, 2.5, 0.251 );
            gluDisk( circleObj, 0.0, 0.25, 12, 1 );
        glPopMatrix();

    glPopMatrix();
}

void ROV::drawPropeller( bool left )
{
    glPushMatrix();

        if( left )
        {
            glTranslatef( 10.0, 0.0, 0.0 );
            glRotatef( 90.0, 0.0, 1.0, 0.0 );
            glRotatef( 45.0, 1.0, 0.0, 0.0 );

            glColor3f( colors[3][0], colors[3][1], colors[3][2] );
            gluCylinder( cylinder, 1, 1, 10, 12, 3 );
        }
        else
        {
            glTranslatef( -10.0, 0.0, 0.0 );
            glRotatef( -90.0, 0.0, 1.0, 0.0 );
            glRotatef( 45.0, 1.0, 0.0, 0.0 );
            
            glColor3f( colors[3][0], colors[3][1], colors[3][2] );
            gluCylinder( cylinder, 1, 1, 10, 12, 3 );
        }

        glPushMatrix();
            glTranslatef( 0.0, 0.0, 10.0 );
            gluSphere( sphere, 3, 12, 12 );

            glPushMatrix();
                if( left )
                    glRotatef( 90.0, 0.0, 1.0, 0.0 );
                else
                    glRotatef( -90.0, 0.0, 1.0, 0.0 );

                gluCylinder( cylinder, 3, 3, 10, 12, 3 );

                glPushMatrix();
                    glTranslatef( 0.0, 0.0, 10.0 );
                    gluSphere( sphere, 3, 12, 12 );

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glColor3f( colors[2][0], colors[2][1], colors[2][2] );
                        gluSphere( sphere, 1, 12, 12 );

                        if( !left )
                            glRotatef( 180.0, 0.0, 0.0, 1.0);
                        drawBlades();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

void ROV::boundBladeAngle()
{
    if( bladeAngle >= 360.0 || bladeAngle <= -360.0 ) bladeAngle = 0.0;
}

void ROV::drawBlades()
{
    glPushMatrix();
        glRotatef( 90.0, 0.0, 1.0, 0.0 );

        bladeAngle += speed[0] + speed[1] + speed[2];

        boundBladeAngle();

        glRotatef( bladeAngle, 1.0, 0.0, 0.0 );

        glScalef( 1.0, 5.0, 5.0 );
        glColor3f( colors[5][0], colors[5][1], colors[5][2] );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );

        glRotatef( 120.0, 1.0, 0.0, 0.0 );
        drawPyramid( false );
    glPopMatrix();
}

void ROV::drawArm()
{
    double angle;

    if( grasping )
        angle = -60.0;
    else
        angle = -45.0;

    boundArmLength();

    glPushMatrix();
        glTranslatef( -5.0, -5.0, 20.0 );
        glColor3f( colors[4][0], colors[4][1], colors[4][2] );
        gluCylinder( cylinder, 1, 1, armLength, 12, 3 );

        glPushMatrix();
            glTranslatef( 0.0, 0.0, armLength );
            gluSphere( sphere, 1, 12, 12 );

            glColor3f( colors[5][0], colors[5][1], colors[5][2] );
            glPushMatrix();
                glRotatef( 90.0, 0.0, 1.0, 0.0 );

                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();

                glRotatef( 120.0, 1.0, 0.0, 0.0 );
                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();

                glRotatef( 120.0, 1.0, 0.0, 0.0 );
                glPushMatrix();
                    glRotatef( angle, 0.0, 1.0, 0.0 );
                    glPushMatrix();
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( false );
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef( 0.0, 0.0, 3.0 );
                        glRotatef( angle, 0.0, 1.0, 0.0 );
                        glScalef( 0.5, 3.0, 3.0 );
                        drawPyramid( true );
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void ROV::boundAcc()
{
    if( speed[0] > 0.01 ) acceleration[0] = -0.03;
    else if( speed[0] < -0.01 ) acceleration[0] = 0.03;
    else acceleration[0] = 0.0;

    if( speed[1] > 0.01 ) acceleration[1] = -0.03;
    else if( speed[1] < -0.01 ) acceleration[1] = 0.03;
    else acceleration[1] = 0.0;

    if( speed[2] > 0.01 ) acceleration[2] = -0.03;
    else if( speed[2] < -0.01 ) acceleration[2] = 0.03;
    else acceleration[2] = 0.0;
}

void ROV::boundSpeed()
{
         if(  acceleration[0] > 0  && speed[0] >  maxSpeed ) speed[0] =  maxSpeed;
    else if(  acceleration[0] < 0  && speed[0] < -maxSpeed ) speed[0] = -maxSpeed;
    else if( !isMoving[0] && fabs(speed[0]) < 0.03 ) speed[0] = 0.0;

         if(  acceleration[1] > 0  && speed[1] >  maxSpeed ) speed[1] =  maxSpeed;
    else if(  acceleration[1] < 0  && speed[1] < -maxSpeed ) speed[1] = -maxSpeed;
    else if( !isMoving[1] && fabs(speed[1]) < 0.03 ) speed[1] = 0.0;

         if(  acceleration[2] > 0  && speed[2] >  maxSpeed ) speed[2] =  maxSpeed;
    else if(  acceleration[2] < 0  && speed[2] < -maxSpeed ) speed[2] = -maxSpeed;
    else if( !isMoving[2] && fabs(speed[2]) < 0.03 ) speed[2] = 0.0;
}

void ROV::boundPos()
{
    if( pos[0] < limitPos[0].first )       pos[0] = limitPos[0].first;
    else if( pos[0] > limitPos[0].second ) pos[0] = limitPos[0].second;

    if( pos[1] < limitPos[1].first)        pos[1] = limitPos[1].first;
    else if( pos[1] > limitPos[1].second ) pos[1] = limitPos[1].second;

    if( pos[2] < limitPos[2].first )       pos[2] = limitPos[2].first;
    else if( pos[2] > limitPos[2].second ) pos[2] = limitPos[2].second;
}

void ROV::boundArmLength()
{
    if( armLength < limitArmLength.first ) armLength = limitArmLength.first;
    else if( armLength > limitArmLength.second ) armLength = limitArmLength.second;
}

void ROV::speedUpDown( bool faster )
{
    if( faster )
    {
        maxSpeed += 0.3;
        if( maxSpeed >= 4.0 ) maxSpeed = 4.0;
    }
    else
    {
        maxSpeed -= 0.3;
        if( maxSpeed <= 1.0 ) maxSpeed = 1.0;
    }
}

void ROV::moving()
{
    speed[0] += acceleration[0];
    speed[1] += acceleration[1];
    speed[2] += acceleration[2];

    boundSpeed();

    pos[0] += speed[0] * facing[0];
    pos[2] += speed[0] * facing[2];

    pos[0] += speed[1] * facing[2];
    pos[2] -= speed[1] * facing[0];

    pos[1] += speed[2];

    boundPos();
}

void ROV::turnLeftRight( bool left )
{
    if( left )
    {
        rotation[0] += 1.0;

        if( rotation[0] >= 360.0 )
            rotation[0] = 0.0;
    }
    else
    {
        rotation[0] -= 1.0;

        if( rotation[0] <= -360.0 )
            rotation[0] = 0.0;
    }
    
    setFacing();
}

void ROV::setFacing()
{
    facing[0] = sin( rotation[0] * PI / 180 );
    facing[2] = cos( rotation[0] * PI / 180 );
}