void display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    pressing();

    switch( viewing )
    {
        case OrthoX:
            changeLookAt( OrthoX );
            makeProjection( OrthoX );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case OrthoY:
            changeLookAt( OrthoY );
            makeProjection( OrthoY );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case OrthoZ:
            changeLookAt( OrthoZ );
            makeProjection( OrthoZ );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case FIRST_VIEW:
            changeLookAt( FIRST_VIEW );
            makeProjection( FIRST_VIEW );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case THIRD_VIEW:
            changeLookAt( THIRD_VIEW );
            makeProjection( THIRD_VIEW );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case GOD_VIEW:
            changeLookAt( GOD_VIEW );
            makeProjection( GOD_VIEW );
            glViewport( 0, 0, windowWidth, windowHeight );
            drawScene();

            glViewport( windowWidth - myInfo2->width, windowHeight - myInfo2->height, myInfo2->width, myInfo2->height );
            myInfo2->showInfo();
            break;

        case EACH_VIEW:
            changeLookAt( OrthoX );
            makeProjection( OrthoX );
            glViewport( 0, windowHeight / 2, windowWidth / 2, windowHeight / 2 );
            drawScene();

            changeLookAt( OrthoY );
            makeProjection( OrthoY );
            glViewport( windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2 );
            drawScene();

            changeLookAt( OrthoZ );
            makeProjection( OrthoZ );
            glViewport( 0, 0, windowWidth / 2, windowHeight / 2 );
            drawScene();

            changeLookAt( FIRST_VIEW );
            makeProjection( FIRST_VIEW );
            glViewport( windowWidth / 2, 0, windowWidth / 2, windowHeight / 2 );
            drawScene();
            break;

        case MY_VIEW:
            changeLookAt( THIRD_VIEW );
            makeProjection( THIRD_VIEW );
            glViewport( 0, windowHeight / 2, windowWidth / 2, windowHeight / 2 );
            drawScene();

            changeLookAt( FIRST_VIEW );
            makeProjection( FIRST_VIEW );
            glViewport( windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2 );
            drawScene();

            changeLookAt( GOD_VIEW );
            makeProjection( GOD_VIEW );
            glViewport( 0, 0, windowWidth / 2, windowHeight / 2 );
            drawScene();

            glViewport( windowWidth / 2, 0, windowWidth / 2, windowHeight / 2);
            myInfo1->showInfo();
            break;

        default: break;
    }

    glutSwapBuffers();
}

void reshape( int newWidth, int newHeight )
{
    windowWidth  = newWidth;
    windowHeight = newHeight;
}

void initWindow()
{
    srand( time( NULL ) );

    glClearColor( 0.05, 0.05, 0.3, 1.0 ); 
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );

    if( !sphere )
    {
        sphere = gluNewQuadric();
        gluQuadricDrawStyle( sphere, GLU_FILL   );
        gluQuadricNormals(   sphere, GLU_SMOOTH );
    }

    if( !cylinder )
    {
        cylinder = gluNewQuadric();
        gluQuadricDrawStyle( sphere, GLU_FILL   );
        gluQuadricNormals(   sphere, GLU_SMOOTH );
    }

    if( !circleObj )
    {
        circleObj = gluNewQuadric();
        gluQuadricDrawStyle( circleObj, GLU_FILL );
    }

    if( !myROV )
    {
        myROV = new ROV();
    }

    if( !myInfo1 )
    {
        myInfo1 = new Info();
    }

    if( !myInfo2 )
    {
        myInfo2 = new Info( (int)(INIT_W * 0.4), (int)(INIT_H * 0.2) );
    }

    initFloor();
    initFishes();
    initStones();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glFlush();
}

void pressing()
{
    myROV->isCollision = fishCollision() || stoneCollision();

    if( myROV->isCollision )
    {
        myROV->speed[0] = -myROV->speed[0];
        myROV->speed[1] = -myROV->speed[1];
        myROV->speed[2] = -myROV->speed[2];

        if( myROV->speed[0] == myROV->speed[1] == myROV->speed[2] == 0 )
        {
            myROV->pos[0] += myROV->collisionVector[0];
            myROV->pos[1] += myROV->collisionVector[1];
            myROV->pos[2] += myROV->collisionVector[2];
        }
    }
    
    unsigned char keyValue;

    myROV->boundAcc();

    for( auto key: pressingKey )
    {
        if( myROV->isCollision )
        {
            break;
        }

        keyValue = tolower( key );

        switch( keyValue )
        {
            case 'w':
                myROV->acceleration[0] = 0.05;
                myROV->isMoving[0] = true;
                break;
                
            case 's':
                myROV->acceleration[0] = -0.05;
                myROV->isMoving[0] = true;
                break;

            case 'a':
                myROV->acceleration[1] = 0.05;
                myROV->isMoving[1] = true;
                break;
                
            case 'd':
                myROV->acceleration[1] = -0.05;
                myROV->isMoving[1] = true;
                break;

            case 'i':
                myROV->acceleration[2] = 0.05;
                myROV->isMoving[2] = true;
                break;
                
            case 'k':
                myROV->acceleration[2] = -0.05;
                myROV->isMoving[2] = true;
                break;
                
            myROV->isMoving = { false, false, false };

            case 'j':
                myROV->turnLeftRight( true );
                break;
                
            case 'l':
                myROV->turnLeftRight( false );
                break;

            case 'u':
                myROV->armLength += 1.0;
                break;

            case 'o':
                myROV->armLength -= 1.0;
                break;

            case 'q':
                myROV->grasping = true;
                break;
            
            case 'z':
                zoomIn();
                break;
            
            case 'x':
                zoomOut();
                break;
                
            case 'c':
                zoomIn( false );
                break;
            
            case 'v':
                zoomOut( false );
                break;
        }
    }

    if( pressingKey.empty() )
    {
        myROV->isMoving = { false, false, false };
    }

    cout << myROV->graspingFish << endl;
    myROV->moving();
}