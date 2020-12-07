void keyCtrl( unsigned char keyValue, int x, int y )
{
    switch( keyValue )
    {
        case ESC:
            exit(0);
            break;

        case SPACE:
            delete myROV;
            myROV = new ROV();
            break;

        case '1':
            viewing = OrthoX;
            break;
            
        case '2':
            viewing = OrthoY;
            break;

        case '3':
            viewing = OrthoZ;
            break;

        case '4':
            viewing = FIRST_VIEW;
            break;
            
        case '5':
            viewing = THIRD_VIEW;
            break;

        case '6':
            viewing = GOD_VIEW;
            break;

        case '7':
            viewing = EACH_VIEW;
            break;

        case '8':
            viewing = MY_VIEW;
            break;

        default: 
            pressingKey.emplace_back( keyValue );
    }
}

void keyUpCtrl( unsigned char keyValue, int posX, int posY )
{
    auto it = find( pressingKey.begin(), pressingKey.end(), keyValue );
    
    if( it != pressingKey.end() )
    {
        if( tolower(*it) == 'q' ) myROV->grasping = false;
        pressingKey.erase( it );
    }
}

void mouseCtrl( int button, int state, int posX, int posY )
{
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
        myROV->speedUpDown( true );
    }
    else if( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN )
    {
        myROV->speedUpDown( false );
    }
}