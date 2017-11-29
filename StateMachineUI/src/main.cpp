#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"
#include <stdio.h>
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.
#include <SDL.h>
#include <string>


struct inv
{
	int potioncount;

};




int main(int argc, char *argv[])
{

	inv inventory = inv();
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	SDL_Window *window = SDL_CreateWindow("State Machine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	gl3wInit();

	bool quit = false;

	ImGui_ImplSdlGL3_Init(window);

//	bool show_test_window = true;
//	bool show_another_window = false;
	bool show_menu = true;
	static bool show_inventory = false;
	static bool show_shop = false;
	const ImVec2& size = ImVec2(200, 400);
	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!quit) {

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSdlGL3_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				quit = true;
		}
		ImGui_ImplSdlGL3_NewFrame(window);


		if(show_menu)
		{
			
			ImGui::Begin("Menu Test", &show_menu);
			ImGui::SetNextWindowSize(size);
			if (ImGui::Selectable("Item Shop", false))
			{
				if (ImGui::IsMouseClicked)
				{
					show_shop = true;
				}
			}
			if (ImGui::Selectable("Inventory", false))
			{
				if (ImGui::IsMouseClicked)
				{
					show_inventory = true;
				}
			}

			if (show_inventory)
			{
				ImGui::OpenPopup("Inventory");
				ImGui::BeginPopupModal("Inventory", &show_inventory);
				const char * c = "";
		
				if (inventory.potioncount > 0) {
					if (ImGui::Selectable("Potions", false))
					{
						if (ImGui::IsMouseClicked)
						{
							inventory.potioncount--;
						}
					}
					ImGui::SameLine(100);
					ImGui::Value(c, inventory.potioncount);
					ImGui::Text(c);
				}
				if (ImGui::Button("Close")) 
				{
					ImGui::CloseCurrentPopup();
					show_inventory = false;
				}
				ImGui::EndPopup();
			}
			if (show_shop)
			{
				ImGui::OpenPopup("Item Shop");
				ImGui::BeginPopupModal("Item Shop", &show_shop);
				static int potions = 0;
				ImGui::Text("Potion");
				ImGui::SameLine();
				ImGui::PushItemWidth(100);
				ImGui::InputInt("", &potions);

				if (ImGui::Button("Buy")) {
					inventory.potioncount += potions;
					potions = 0;
				}
				ImGui::SameLine();
				if (ImGui::Button("Close"))
				{
					ImGui::CloseCurrentPopup();
					show_shop = false;
				}
				ImGui::EndPopup();
			}
		
			ImGui::End();

		}

		// Rendering
		glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		SDL_GL_SwapWindow(window);
	}

	// Cleanup
	ImGui_ImplSdlGL3_Shutdown();
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}