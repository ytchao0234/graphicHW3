void changeLookAt( int viewMode )
{
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    switch( viewMode )
    {
        case OrthoX:
            gluLookAt( 1.0, 0.0, 0.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;
        case OrthoY:
            gluLookAt( 0.0, 1.0, 0.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 0.0, 1.0 ); // v up
            break;
        case OrthoZ:
            gluLookAt( 0.0, 0.0, 1.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;
        case FIRST_VIEW:
            gluLookAt( myROV->pos[0] + myROV->facing[0] * 20.0, // eye position
                       myROV->pos[1] + myROV->facing[1] * 20.0,
                       myROV->pos[2] + myROV->facing[2] * 20.0,

                       myROV->pos[0] + myROV->facing[0] * 150.0, // look position
                       myROV->pos[1] + myROV->facing[1] * 150.0,
                       myROV->pos[2] + myROV->facing[2] * 150.0,

                       0.0, 1.0, 0.0 ); // v up
            break;
        case THIRD_VIEW:
            gluLookAt( myROV->pos[0] + myROV->facing[0] * -120.0, // eye position
                       myROV->pos[1] + myROV->facing[1] * -120.0 + 50.0,
                       myROV->pos[2] + myROV->facing[2] * -120.0,

                       myROV->pos[0], myROV->pos[1], myROV->pos[2], // look position
                       
                       0.0, 1.0, 0.0 ); // v up
            break;
        case GOD_VIEW:
            gluLookAt( -75.0, 120.0, -120.0, // eye position
                       0.0, 0.0, 0.0, // look position
                       0.0, 1.0, 0.0 ); // v up
            break;

        default: break;
    }
}

void makeProjection( int viewMode )
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    double w =  (double)windowWidth;
    double h =  (double)windowHeight;

    if( viewMode <= OrthoZ ) // OrthoX, OrthoY, OrthoZ
    {
        if( w > h )
        {
            glOrtho(-300.0, 300.0,
                    -300.0 * h/w, 300.0 * h/w,
                    -300.0, 300.0);
        }
        else
        {
            glOrtho(-300.0 * w/h, 300.0 * w/h,
                    -300.0, 300.0, 
                    -300.0, 300.0);
        }
    }
    else // FIRST_VIEW, THIRD_VIEW, GOD_VIEW
    {
        gluPerspective( 90.0, w/h, 1.5, 400.0);
    }

    glMatrixMode( GL_MODELVIEW );
}