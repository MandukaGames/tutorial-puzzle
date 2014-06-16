//
//  MDPauseMenuInterfaz.h
//  Enigma
//
//  Created by rubenvot on 05/03/14.
//
//

#ifndef Enigma_MDPauseMenuInterfaz_h
#define Enigma_MDPauseMenuInterfaz_h

class MDPauseMenuInterfaz
{
    
public:
    virtual void shouldPauseGame()  =0;
    virtual void shouldResumeGame() =0;
    virtual void shouldRetryGame()  =0;
    virtual void shouldQuitGame()   =0;
};


#endif
