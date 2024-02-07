#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>

// Convert sf::Color to ImVec4 using ImGui's utility function
static ImVec4 sfColorToImVec4(sf::Color color)
{
	return ImGui::ColorConvertU32ToFloat4(ImGui::ColorConvertFloat4ToU32({ color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f }));
}

// Convert ImVec4 to sf::Color using ImGui's utility function
static sf::Color ImVec4TosfColor(ImVec4 color)
{
	return sf::Color(static_cast<sf::Uint8>(color.x * 255.0f),
		static_cast<sf::Uint8>(color.y * 255.0f),
		static_cast<sf::Uint8>(color.z * 255.0f),
		static_cast<sf::Uint8>(color.w * 255.0f));
}

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	ImGui::SFML::Init(window);

	// ImGui Temp Setup
	bool drawShape = true;
	sf::Color myColor = sf::Color::Red;
	float myVelocity[2] = { 1.1f, 1.1f };
	float myScale = 1.0f;
	char myName[] = "This is a name";

	sf::CircleShape myCircle;
	myCircle.setRadius(20.5f);
	myCircle.setPosition(sf::Vector2f(1.0f, 1.0f));

	sf::Font font;
	if (!font.loadFromFile("fonts/tech.ttf"))
	{
		return EXIT_FAILURE;
	}

	sf::Text text("Hello SFML", font, 50);

	sf::Clock deltaClock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		ImGui::Begin("Shape Properties");
		if (ImGui::BeginCombo("Shape", myName))
		{
			ImGui::EndCombo();
		}
		ImGui::Checkbox("Draw Shape", &drawShape);
		ImGui::SliderFloat("Scale", &myScale, 0.0f, 10.0f);
		ImGui::SliderFloat2("Velocity", myVelocity, 0.0f, 10.0f);

		ImVec4 colorFloat = sfColorToImVec4(myColor);
		if (ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&colorFloat)))
		{
			myColor = ImVec4TosfColor(colorFloat);
		}

		ImGui::InputText("Name", myName, sizeof(myName));
		ImGui::End();

		myCircle.setFillColor(myColor);

		window.clear();
		window.draw(text);
		if (drawShape)
		{
			window.draw(myCircle);
		}

		ImGui::SFML::Render(window);

		window.display();
	}

	ImGui::SFML::Shutdown();

	return EXIT_SUCCESS;
}
