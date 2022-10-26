#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string> 


int main()
{
	std::srand(std::time(nullptr));
	bool exit = false;

	const sf::Uint16 numColor = 16;
	const sf::Uint16 winSize = 1000;

	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.sRgbCapable = true;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(winSize, winSize), "press E for refresh field", sf::Style::Titlebar | sf::Style::Close, contextSettings);

	window.setFramerateLimit(60);


	// Initialise GLEW for the extended functions.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		return EXIT_FAILURE;

	// Create a clock for measuring the time elapsed
	sf::Clock clock;
	sf::Time time1 = clock.getElapsedTime();
	sf::Time time2 = clock.getElapsedTime();
	sf::Uint16 fps = 0;







	// content
	sf::Glsl::Vec4	colors[numColor] = {	sf::Glsl::Vec4(0, 0, 0, 255),
											sf::Glsl::Vec4(15, 15, 15, 255),
											sf::Glsl::Vec4(0, 0, 255, 255),
											sf::Glsl::Vec4(15, 15, 255, 255),
											sf::Glsl::Vec4(0, 255, 0, 255),
											sf::Glsl::Vec4(15, 255, 15, 255),
											sf::Glsl::Vec4(0, 255, 255, 255),
											sf::Glsl::Vec4(15, 255, 255, 255),
											sf::Glsl::Vec4(255, 0, 0, 255),
											sf::Glsl::Vec4(255, 15, 15, 255),
											sf::Glsl::Vec4(255, 0, 255, 255),
											sf::Glsl::Vec4(255, 15, 255, 255),
											sf::Glsl::Vec4(255, 255, 0, 255),
											sf::Glsl::Vec4(255, 255, 15, 255),
											sf::Glsl::Vec4(255, 255, 255, 255),
											sf::Glsl::Vec4(255, 255, 240, 255)
	};



	//rendertexture
	sf::RenderTexture texture;
	if (!texture.create(winSize, winSize, contextSettings))
		return -1;

	texture.clear(sf::Color::Blue);
	sf::RectangleShape rectangle(sf::Vector2f(1U, 1U));
	for (int i = 0; i < winSize; i++)
	{
		for (int j = 0; j < winSize; j++)
		{
			rectangle.setPosition(j,i);
			int c = rand() % numColor;
			rectangle.setFillColor(sf::Color(colors[c].x, colors[c].y, colors[c].z, 255U));
			texture.draw(rectangle);

		}
	}
	
	texture.display();

	//data texture

	sf::Sprite sprite;
	sf::Texture tex;
	tex.create(winSize, winSize);

	tex.update(texture.getTexture());
	sprite.setTexture(tex);


	//window triangles

	float vertices[] = {
	-1.0f,	-1.0f, 0.0f, 0, 1,
	-1.0f,	1.0f, 0.0f, 0, 0,
	 1.0f,	1.0f, 0.0f, 1, 0,
	 1.0f,	-1.0f, 0.0f, 1, 1
	};
	unsigned int indices[] = { 
		0, 1, 2,
		0, 2, 3 
	};


	//shader

	sf::Shader sh;
	sh.loadFromFile("Shaders/screen.vert", "Shaders/screen.frag");

	if (!sh.isAvailable()) {
		std::cout << "The shader is not available\n";
	}


	//buf objects

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);



	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	//game loop
	while (!exit)
	{




		//fps
		time2 = clock.getElapsedTime();
		fps++;
		if ((time2.asSeconds() - time1.asSeconds()) >= 1.0)
		{
			std::string s = std::to_string(fps);
			window.setTitle("press E for refresh field, FPS: " + s);
			fps = 0;
			time1 = time2;

		}


		//process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close window: exit
			if (event.type == sf::Event::Closed)
			{
				exit = true;

				break;
			}

			//escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				exit = true;
				break;
			}

			//refresh field
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				
				for (int i = 0; i < winSize; i++)
				{
					for (int j = 0; j < winSize; j++)
					{
						rectangle.setPosition(j, i);
						int c = rand() % numColor;
						rectangle.setFillColor(sf::Color(colors[c].x, colors[c].y, colors[c].z, 255U));
						texture.draw(rectangle);

					}
				}

				texture.display();
				tex.update(texture.getTexture());
				sprite.setTexture(tex);
			}
		}

		



		//render on screen
		window.setActive(true);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		window.setActive(false);
		
		window.draw(sprite);
		window.display();


		//update rendertexture
		texture.setActive(true);

		glBindVertexArray(VAO);
		sf::Shader::bind(&sh);
		sh.setUniform("tex", tex);
		sh.setUniformArray("colors", colors, numColor);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		sf::Shader::bind(nullptr);
		glBindVertexArray(0);
	

		texture.display();
		texture.setActive(false);


		//update data texture

		tex.update(texture.getTexture());
		sprite.setTexture(tex);


	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

	window.close();

	return EXIT_SUCCESS;
}
