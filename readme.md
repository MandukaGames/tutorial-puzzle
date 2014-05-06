#Creando un puzzle con cocos2dx v3 C++

_En éste tutorial vamos a crear desde cero un juego que consiste en crear un puzzle. Nuestro puzzle tendrá cuatro piezas, pero si te gusta cómo funciona y te sientes con ganas de experimentar podrías extenderlo y agregarle más piezas (o más elementos de gamificación!). Simplemente haznos saber tus impresiones y cómo te ha ayudado a construir tu propio juego._

## Entorno de desarrollo

La nueva versión 3.0 de cocos2d-x ha supuesto un paso enorme en el desarrollo del motor. Si todavía estás usando la versión 2 deberías plantearte migrar lo antes posible. 

En éste tutorial daremos por supuesto que ya te has descargado cocos 2dx a tu ordenador y has instalado la nueva _console tool_. Si no es así te recomendamos que te pases por el  [github oficial](https://github.com/cocos2d/cocos2d-x) de cocos2d-x. Allí encontrarás todo lo que necesitas.

Por último, para el desarrollo de éste tutorial usaremos la última versión de OS X y por comodidad compilaremos el juego directamente para mac, pero todo lo que hacemos será compatible con otros sistemas operativos, __incluídos iOS y Android__. 

¡Manos a la obra!

##Creando un nuevo proyecto con Cocos2dx v3

Lo primero que debemos hacer es crear un nuevo proyecto. En éste caso yo lo crearé en el escritorio. Así que abre el terminal y crea un nuevo proyecto con la console tool cocos. 

_A continuación te dejamos como ejemplo la salida de nuestra consola_:

	Rubens-MacBook-Pro:bin Vot$ cocos new PuzzleTutorial -p com.mandukagames.puzzle -l cpp -d /Users/Ruben/Desktop 
	Runing command: new
	> Copy template into /Users/Vot/Desktop/PuzzleTutorial
	> Copying cocos2d-x files...
	> Rename project name from 'HelloCpp' to 'PuzzleTutorial'
	> Replace the project name from 'HelloCpp' to 'PuzzleTutorial'
	> Replace the project package name from 'org.cocos2dx.hellocpp' to 'com.mandukagames.puzzle'

Si todo ha ido bien en tu escritorio deberías tener un nuevo proyecto de Cocos2d-x llamado "PuzzleTutorial". Ahora simplemente vete a la carpeta _proj.ios_mac_ y abre el archivo _PuzzleTutorial.xcodeproj_

![Imagen001](Link.png)

La mejor forma de probar que todo ha ido bien es ejecutar el proyecto por primera vez. Así que al lado de los botones play-stop selecciona el target _PuzzleTutorial Mac_ y hazlo correr en _My Mac_. Se abrirá una nueva ventana de OSX ejecutando el código base de cocos2dx. 

![Imagen002](Link.png)

##Personalizando el nuevo proyecto y creando nuevas clases

Ahora podríamos arrancar ya directamente y empezar a escribir nuestro juego. Sin embargo a mí no me gusta tener un archivo que se llama _HelloWorldScene_ por ello, lo primero que vamos a hacer es renombrarlo a _GamePlayScene_. (Si tu karma no se siente afectado por éste hecho simplemente sáltate éste paso ;-). Del mismo modo, la clase _HelloWorld_ la renombraremos a _GamePlay_ y haremos todos los cambios necesarios en el código. Lo más sencillo es que uses la función de Xcode "Find & replace" y cambies todas las ocurrencias de 
"HelloWorld" por "GamePlay". Una vez termines pulsa cmd+b para compilar comprobar que todo está en orden.

Nuestro puzzle estará formado por un _Layer_ que usaremos como "lienzo" y cuatro piezas que el usuario podrá mover hasta encajar en su lugar adecuado. De modo que éste es un buen momento para crear la clase  _Piece_ que heredará de Sprite. 
Después agregaremos los recursos tanto para el lienzo como para las piezas. 

En éste caso nosotros hemos creado un pequeño puzzle con el logotipo de Manduka que te puedes [descargar aquí](http://link-descarga). Pero puedes personalizarlo y usar las imágenes que más te gusten. 

El inspector de ficheros de Xcode debería quedar así:
![Imagen003](Link.png)

##Ha llegado el momento de escribir código

### Borrar código innecesario
Lo primero que vamos a hacer es borrar el código innecesario que cocos ha escrito para nosotros en la clase _GamePlay_. De modo que nuestro método _init_ quede como el siguiente: 

	// on "init" you need to initialize your instance
	bool GamePlay::init()
	{
		if ( !Layer::init() )
		{
			return false;
		}
		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vector2 origin = Director::getInstance()->getVisibleOrigin();
		return true;
	}

También podemos borrar el método _menuCloseCallback_ (y su declaración en el header) ya que no lo vamos a utilizar.

### Añadir background y cambiar color de fondo

Con la finalidad de que los usuarios sepan dónde colocar las piezas agregaremos una imagen a la escena que usaremos como background y la posicionaremos en el centro. 

_Fíjate en que hemos marcado con el símbolo "+" las líneas que debes agregar_

	// on "init" you need to initialize your instance
	bool GamePlay::init()
	{
	    //////////////////////////////
	    // 1. super init first
	    if ( !Layer::init() )
	    {
	        return false;
	    }
	    
	    Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vector2 origin = Director::getInstance()->getVisibleOrigin();

	    +// Add Background shape
	    +Sprite * background = Sprite::create("background.png");
	    +background->setPosition(Vector2(this->getContentSize().width/2, this->getContentSize().height/2));
	    +this->addChild(background);
	    
	    return true;
	}
	
Una cosa, no necesaria, pero que también haremos para confort personal es cambiar el color de fondo de la escena. Para ello basta con cambiar la herencia de la clase de _Layer_ a _LayerColor_: 
	
	class GamePlay : public cocos2d::LayerColor
	
Y sustituiremos la llamada a init por otra que nos permita elegir un color: 

	- if (!Layer::init())
	+ if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))

### Agregando las coordenadas de las piezas

Ahora vamos a ocuparnos del posicionamiento de las piezas. Si éste tutorial te gusta mucho y finalmente decides desarrollar un juego de verdad a partir de él deberás crear algún método sofisticado para posicionar las piezas en la pantalla. Estaría bien crear algún formato basado en .plist en el que creases un array de piezas con el nombre de la imagen y su posición en la pantalla. Ésto te permitiría agregar más puzzles (niveles) fácilmente. Sin embargo no es objeto de éste tutorial profundizar en éstos temas, por ello aquí simplemente escribiremos en el propio código la posición inicial y final de cada pieza. 
_Si hay suficiente gente interesada prometemos hacer una segunda parte del tutorial explicando técnicas para crear niveles_

A la hora de calcular la posición de las piezas ten en cuenta que debes recordar el anchor point que luego asignarás a tus sprites. En nuestro caso lo dejaremos por defecto - (0.5, 0.5) -  el centro exacto de las piezas. 

#### Posición final

A partir del bakcground y un poco de geometría básica calculamos la posición correcta de las piezas del puzle. 

    // Position of pieces
    Vector2 positionPieceTopLeft     = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceTopRight    = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()+ background->getContentSize().height/4);
    
    Vector2 positionPieceBottomLeft  = Vector2(background->getPositionX()- background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);
    
    Vector2 positionPieceBottomRight = Vector2(background->getPositionX()+ background->getContentSize().width/4,
                                               background->getPositionY()- background->getContentSize().height/4);


### La clase pieza

__Previamente habíamos creado la clase __Piece__ ahora es el momento de darle forma. __

Empezaremos por la definición de la clase. Simplemente vete al fichero Piece.h y pega el siguiente código. No te preocupes si no entiendes algo, a continuación veremos su significado. 

	#include "cocos2d.h"

	USING_NS_CC;

	class Piece: public Sprite
	{
	    bool _actived;
	    Vector2 _targetPosition;
	    
	    void setActived(bool active);
	    
	public:
	        
	    // Constructor
	    static PLPiece* create(const std::string &filename);
	    virtual bool init(const std::string &filename);
    
	    void setTargetPosition(Vector2 targetPosition);
	    bool currentLocationSuccess();
	};

Como vemos, nuestras piezas de puzle serán sprites. Definiremos las funciones _create_ e _init_ personalizadas para poder inicializar la pieza con la imagen deseada (que pasaremos como parámetro). 

Hemos definido dos variables de instancia __actived_ y __targetPosition_:

*  ___actived__  nos sirve para identificar si la pieza está activa en un momento determinado, es decir, si el usuario la está tocando en un preciso momento. Usaremos ésta variable para saber cuando debemos dar feedback al usuario. Por ejemplo si el usuario está tocando la pieza podemos hacerla un poco más grande o cambiarla de color. 
*   En ___targetPosition__  almacenaremos el punto exacto en el cual consideramos que la pieza está bien colocada. Fíjate que también hemos definido un setter público para ésta variable. Podríamos haber definido directamente la variable como pública. Pero cada vez que haces eso un gatito muere en el mundo.

Por último hemos definido un método al que le podemos preguntar si la posición de la pieza en ese preciso instante es la posición final que debería tener. Nos será muy útil cuando implementemos la lógica de las piezas. 

#### Constructores 

Vamos a empezar la implementación por los métodos básicos: *create* e *init*. 

Éstos dos métodos son un patrón estandar para crear clases en Cocos2d-x. Si eres un veterano de Cocos2d-x probablemente ya te los sepas de memoria y si no pronto te los aprenderás porque los escribirás un montón de veces. Si no sabes lo que significan o simplemente sientes curiosidad por ellos te recomendamos que vayas a la documentación oficial de [Cocos2d-x](http://www.cocos2d-x.org/wiki) dónde hay una sección dedicada a la gestión de memoria y el patrón retain /release.

	Piece* Piece::create(const std::string &filename)
	{
	    Piece *pRet = new Piece();
		if (pRet && pRet->init(filename))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = NULL;
		}
	    return pRet;

	}


	bool Piece::init(const std::string &filename)
	{
	    if (!Sprite::initWithFile(filename)) {
	        return false;
	    }

	    return true;
	}
		
	void Piece::setTargetPosition(cocos2d::math::Vector2 targetPosition)
	{
	    this->_targetPosition = targetPosition;
	}
Fíjate que también hemos aprovechado para crear el setter de __targetPosition_. Llegados a este punto simplemente comenta los métodos que todavía no hemos implementado y cmd+r para compilar y correr nuestro juego. Así nos aseguraremos de que todo está en orden. 

Tal como dicen en los programas de cocina. Retiramos del fuego y reservamos durante unos minutos. 

### Agregando las piezas a la escena

Podríamos agregar cada pieza del puzzle una tras otra. Sin embargo aprovecharemos este punto para hacer un breve inciso y ver también por encima la nueva clase _Vector_ que sustituye a _CCArray_. 

Si volvemos a nuestra clase GamePlay veremos que habíamos agregado la posición de de las piezas. Teníamos cuatro variables almacenando posiciones de la pantalla. Ahora vamos a crear las piezas y asignar cada posición a una pieza distinta y para ello vamos a utilizar un bucle for. Así solo escribiremos el código una vez. Para ello necesitamos previamente introducir las posiciones (Vector2) en un array. Añadimos las siguientes líneas al método init de GamePlay

	Vector2 positionsArray[4];
	positionsArray[0] = positionPieceTopLeft;
	positionsArray[1] = positionPieceTopRight;
	positionsArray[2] = positionPieceBottomLeft;
	positionsArray[3] = positionPieceBottomRight;

Y a continuación simplemente creamos y agregamos una pieza por cada posición objetivo.

    for (int i = 0; i < 4; i++)
    {
        // Add piece
        Piece * piece = Piece::create("piece_0"+std::to_string(i)+".png");
        piece->setTargetPosition(positionsArray[i]);
        this->addChild(piece);
    }

En éste momento ya podemos compilar y ejecutar y efectivamente nuestras piezas se agregarán en el punto (0,0). 

![Imagen003](Link.png)

A continuación agregaremos interacción a las piezas y la capacidad de moverse. Pero para ello primero debemos crear una referencia. Y qué mejor que un nuevo y flamante _Vector_. La clase CCArray ha quedado obsoleta. La clase Vector está basada en la librería standard de C++ y tiene algunas ventajas respecto a CCArray. Puedes encontrar una buena descripción al respecto en [éste artículo](http://dev.bunnyhero.org/2014/01/cocos2d-x-30-beta-the-new-vector-class/) de Wayne A.Lee. (O puedes simplemente fiarte y seguir con el tutorial). 

Creamos una nueva variable de instancia en GamePlay.h. La marcaremos como privada ya que nadie debería tener acceso a ella más que los propios objetos de la clase. 

	private:
	    Vector<Piece *> puzzlePieces;
        
Y ahora agregaremos la línea marcada con el carácter + 

	for (int i = 0; i < 4; i++)
	{
		// Add piece
		Piece * piece = Piece::create("piece_0"+std::to_string(i)+".png");
		piece->setTargetPosition(positionsArray[i]);
		+ this->puzzlePieces.pushBack(piece);
		this->addChild(piece);
	}

Con ésto ya tenemos referenciadas las piezas del puzzle, de modo que ya podemos volver a la clase Piece y agregar interacción. 

### Agregando Interacción

Cocos2d-x v3 ha introducido algunas mejoras en la gestión de eventos. Te recomendamos encarecidamente que te revises el siguiente apartado de la documentación oficial sobre [event handling](http://www.cocos2d-x.org/docs/manual/framework/native/input/event-dispatcher/en). 

Lo primero que haremos será declarar los callbacks en Piece.h: 

	bool onTouchBegan(Touch*, Event*);
	void onTouchMoved(Touch*, Event*);
	void onTouchEnded(Touch*, Event*);
	void onTouchCancel(Touch*, Event*);
	
Yo los he nombrado de ésta manera para mantener un poco el standard, pero podrían llamarse de cualquier otra forma (de hecho, incluso podríamos declararlos en línea) lo único importante es que el tipo de retorno y los parámetros coincidan. 

En la implementación del método init agregaremos el siguiente código. Que lo único que hace es registrar un nuevo EventListener para los _touchs_ y decirle cuales son los callbacks que debe ejecutar. 

    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Piece::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Piece::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Piece::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Piece::onTouchCancel, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
Y ahora vamos a implementar una de las partes más divertidas. La lógica del juego. 

Queremos que cuando un usuario toque sobre una pieza ésta se active. Para ello, lo que vamos a hacer es comprobar si el touch se produce sobre la pieza que se está tocando.

	bool Piece::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->getBoundingBox().containsPoint(touch->getLocation()))
	    {
	        this->setActived(true);
	    }
	    
	    return true;
	}

Cuando el usuario suelte la pieza ésta se debe desactivar. 

	void Piece::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    this->setActived(false);
	}
	
Si el usuario está pulsando la pieza y se mueve, la pieza también debe moverse: 

	void Piece::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->_actived)
	    {
	        this->setPosition(Vector2(this->getPositionX()+touch->getDelta().x, this->getPositionY()+touch->getDelta().y));
	    }
	}
	
**Es el momento de compilar y ejecutar**
![Imagen](http://enlace)

Si pulsas sobre una pieza y arrastras, además de la emoción de ver a la pieza moviéndose, te habrás dado cuenta de que... ¡No hay rastro de las otras tres piezas! 

Tranquilo, en realidad sí que están en la pantalla, lo que sucede es que estás al pulsar sobre una pieza estás arrastrándolas todas ya que el touch se propaga hacia abajo y afecta a todos los _listeners_ que están en la misma posición. Para evitarlo, haremos la siguiente modificación en el método onTouchBegin. Ahora el touch solo se propagará si estamos pulsando fuera de la pieza. Cuando pulsemos dentro el touch será absorvido por la pieza que estamos pulsando y no tendrá efectos sobre las capas inferiores.  

	bool Piece::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    if (this->getBoundingBox().containsPoint(touch->getLocation()))
	    {
	        this->listener->setSwallowTouches(true);
	        this->setActived(true);
	    }
	    else
	    {
	        this->listener->setSwallowTouches(false);
	    }
	    
	    return true;
	}
	
**Vuelve a compilar y ejecutar** y ahora todo debería ir bien. 
![Imagen](http://enlace)

### ¡Un poco de magia!

Estamos muy orgullosos de que hayas llegado hasta aquí. ¡Eres un tipo duro! 
El mundo necesita más gente como tú. Así que no desfallezcas ahora porque estamos llegando al final. 

Recapitulemos: ya tenemos nuestro tablero, las piezas de nuestro puzle, las posiciones en las que deben ir esas piezas, hemos agregado eventos que permiten moverlas y nuestro puzzle ya se puede montar. Pero queremos que se comporte como un juego de verdad. Así que vamos a agregar un poco feedback para proporcionar una mejor experiencia de usuario. 

Vamos a hacer que cuando el usuario pulsa sobre una pieza y la activa ésta crezca un poco. Para ello nos vamos a valer del método _setActive_ que vamos a modificar de la siguiente manera: 

	void Piece::setActived(bool active)
	{
	    _actived = active;
	    Action *scale;
	    if (_actived)
	    {
	        scale = ScaleTo::create(0.2, 1.1);
	    }
	    else
	    {
	        scale = ScaleTo::create(0.2, 1);
	    }
	    this->runAction(scale);
	}

Así cada vez que tocamos una pieza ésta reaccionará creciendo un 10% y cada vez que la soltamos volverá a su tamaño original. Siéntete libre para compilar y probar a tu antojo. 

Por último... 

¿Recuerdas aquel método que dejamos comentado hace rato?

 **bool currentLocationSuccess**

Ha llegado el momento de descomentarlo. Lo que vamos a hacer ahora es que cuando el usuario libera una pieza, si esta está muy cerca de su destino final nosotros la moveremos al punto exacto. Para ello primero implementamos el método que compruebe si está en el lugar adecuado: 

	bool Piece::currentLocationSuccess()
	{
	    Vector2 currentPosition = this->getPosition();
	    int deltaX, deltaY;
	    deltaX = _targetPosition.x - currentPosition.x;
	    deltaY = _targetPosition.y - currentPosition.y;
	    
		// Current piece is inside the desired range.
	    if ((abs(deltaX) < LOCATION_ACCURACY)&&(abs(deltaY) < LOCATION_ACCURACY))
	    {
	        Action* moveToTargetPosition = MoveTo::create(0.2, _targetPosition);
	        this->runAction(moveToTargetPosition);
	        std::cout << "pieze is now in the correct place";
	        return true;
	    }
	    return false;
	}
	
y lanzamos este método desde el final del touch

	void Piece::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
	{
	    this->setActived(false);
	    this->currentLocationSuccess();
	}
	
Te habrás fijado en que hacemos uso de la constante "LOCATION_ACCURACY". Ésta constante, cómo podrás deducir del código es la precisión con la que queremos detectar si las piezas están en la posición correcta. En el tutorial actual y con las imágenes de muestra "100" ha resultado ser un valor aceptable, pero puedes modificarlo a tu antojo. Cuanto más pequeño más esfuerzo deberá hacer el usuario para colocar las piezas en el sitio correcto. 

¡Y eso es todo! Has completado el tutorial. 

¿Y ahora qué?

## Posibles mejoras 

Te proponemos una lista de mejoras que puedes realizar para practicar: 

* Colocar las piezas aleatoriamente en la pantalla para que el usuario tenga que buscarlas. 
* Un pop up felicitando al usuario cuando las piezas han sido colocadas en su lugar correspondiente. 
* Un botón de reset. 
* Un contador que puntúe al usuario según el tiempo que ha necesitado para resolver el puzzle. 

Si te animas te agradeceríamos que nos enviases tus mejoras por correo a developer@mandukagames.com y así podríamos agregarlas al tutorial. 

That´s all. 
