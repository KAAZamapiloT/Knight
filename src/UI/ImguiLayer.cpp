#include "ImguiLayer.hpp"
#include"imgui.h"

#include"SDL3/SDL.h"
#include"Core/Application.hpp"
#include "imgui_impl_opengl3.h"
#include"imgui_impl_sdl3.h"
#include"Event/WindowEvent.hpp"
#include"Event/EventDispatcher.hpp"
#include"Event/KeyEvent.hpp"
KnightEngine::ImguiLayer::ImguiLayer() : Layer("ImguiLayer")
{
}

KnightEngine::ImguiLayer::~ImguiLayer()
{
	
}

void KnightEngine::ImguiLayer::OnAttach()
{
    KE_TAG_LOG_INFO("ImguiLayer", "Attaching Imgui Layer");

    // Create context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls (optional)
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    // Backend flags
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // IMPORTANT: Initialize SDL3 backend FIRST, then OpenGL
    bool sdl_init_success = ImGui_ImplSDL3_InitForOpenGL(
        Application::GetInstance()->GetWindow().GetNativeWindow(),
        Application::GetInstance()->GetWindow().GetSDLGLContext()
    );

    bool opengl_init_success = ImGui_ImplOpenGL3_Init("#version 410");

    if (!sdl_init_success || !opengl_init_success) {
        KE_TAG_LOG_CRITICAL("ImguiLayer", "Failed to initialize ImGui backends");
    }

    KE_TAG_LOG_INFO("ImguiLayer", "ImGui Layer attached successfully");
	
   
}

void KnightEngine::ImguiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();   // Shutdown OpenGL backend
	ImGui_ImplSDL3_Shutdown();      // Shutdown SDL3 backend
	ImGui::DestroyContext();        // Destroy ImGui context
}



void KnightEngine::ImguiLayer::OnImGuiRender()
{
    static bool p = true;
    ImGui::ShowDemoWindow(&p);
 

}

void KnightEngine::ImguiLayer::Begin()
{
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame(); // Start a new ImGui frame
}

void KnightEngine::ImguiLayer::End()
{
    ImGuiIO& io = ImGui::GetIO();
    Application* app = Application::GetInstance();

    int w = app->GetWindow().GetWidth();
    int h = app->GetWindow().GetHeight();
    io.DisplaySize = ImVec2((float)w, (float)h);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
    // 2. Handle viewports
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window =app->GetWindow().GetNativeWindow() ;
        SDL_GLContext backup_context = app->GetWindow().GetSDLGLContext();
      
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
       
        SDL_GL_MakeCurrent(backup_current_window, backup_context);
       
    }
  
}


void KnightEngine::ImguiLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	if (event.IsHandled()) {
		KE_TAG_LOG_CRITICAL("INGUI_LAYER", "Event already handled, skipping ImguiLayer processing");
		return;
	}
		

	dispatcher.Dispatch<MouseButtonPressedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnMouseButtonPressedEvent));
	dispatcher.Dispatch <MouseButtonReleasedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseScrolledEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnMouseScrolledEvent));
	dispatcher.Dispatch<KeyPressedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnKeyReleasedEvent));
	dispatcher.Dispatch<WindowResizeEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnWindowResizeEvent));
	dispatcher.Dispatch<KeyTypedEvent>(KNIGHT_BIND_FN(KnightEngine::ImguiLayer::OnKeyTypedEvent));
	

}

bool KnightEngine::ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
   // ImGui::GetIO().MouseDrawCursor = true;
	//io.MouseDown[event.GetButton()] = true; // Set the mouse button state to pressed
	io.AddMouseButtonEvent(SDL_MOUSE_TO_IMGUI(event.GetButton()), true); // Add mouse button event

    
	return false;
}

bool KnightEngine::ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
   // ImGui::GetIO().MouseDrawCursor = true;
	//io.MouseDown[event.GetButton()] = false; // Set the mouse button state to released
    io.AddMouseButtonEvent(SDL_MOUSE_TO_IMGUI(event.GetButton()), false);; // Add mouse button event
	
	return false;
}

bool KnightEngine::ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
  //  ImGui::GetIO().MouseDrawCursor = true;
	io.MousePos = ImVec2((float)event.GetX(), (float)event.GetY());
	//io.AddMousePosEvent(event.GetX(), event.GetY());
	io.AddMousePosEvent(io.MousePos.x, io.MousePos.y); // Add mouse position event
	

	return false;
}

bool KnightEngine::ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	//ImGui::GetIO().MouseDrawCursor = true;
	//io.MouseWheel += event.GetYOffset(); // Accumulate vertical scroll
	//io.MouseWheelH += event.GetXOffset(); // Accumulate horizontal scroll
	io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());
	
	return false;
}

bool KnightEngine::ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	io.AddKeyEvent(SDL_TO_ImGuiKey(event.GetKeyCode(), event.GetScanCode()), true); // Add key pressed event
	io.KeyCtrl = io.KeyCtrl || event.GetMod(); // Update Ctrl state
	io.KeyShift = io.KeyShift || event.GetMod(); // Update Shift state
	io.KeyAlt = io.KeyAlt || event.GetMod(); // Update Alt state
	io.KeySuper = io.KeySuper || event.GetMod(); // Update Super state

   
    
    return false;
}

bool KnightEngine::ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddKeyEvent(SDL_TO_ImGuiKey(event.GetKeyCode(), event.GetScanCode()), false); // Add key pressed event
 
   
    
    return false;
}

bool KnightEngine::ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)event.GetWidth(), (float)event.GetHeight());
	KE_TAG_LOG_INFO("ImguiLayer", "Window Resized: {}x{}", event.GetWidth(), event.GetHeight());
	return false;
}

bool KnightEngine::ImguiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	int k = event.GetCharacterCode();
    if(k>0&&k<0x10000)
    io.AddInputCharacter((unsigned int)event.GetCharacterCode());// Add character input event
	
    return false;
}



int KnightEngine::ImguiLayer::SDL_MOUSE_TO_IMGUI(int sdlButton)
{
    switch (sdlButton)
    {
    case SDL_BUTTON_LEFT:   return 0; // ImGui: Left mouse button
    case SDL_BUTTON_RIGHT:  return 1; // ImGui: Right mouse button
    case SDL_BUTTON_MIDDLE: return 2; // ImGui: Middle mouse button
    case SDL_BUTTON_X1:     return 3; // ImGui: Extra mouse button 1
    case SDL_BUTTON_X2:     return 4; // ImGui: Extra mouse button 2
    default:                return -1; // Invalid button
    }
}

ImGuiKey KnightEngine::ImguiLayer::SDL_TO_ImGuiKey(int KeyCode,int ScanCode) {



    // Keypad doesn't have individual key values in SDL3
    switch (ScanCode)
    {
    case SDL_SCANCODE_KP_0: return ImGuiKey_Keypad0;
    case SDL_SCANCODE_KP_1: return ImGuiKey_Keypad1;
    case SDL_SCANCODE_KP_2: return ImGuiKey_Keypad2;
    case SDL_SCANCODE_KP_3: return ImGuiKey_Keypad3;
    case SDL_SCANCODE_KP_4: return ImGuiKey_Keypad4;
    case SDL_SCANCODE_KP_5: return ImGuiKey_Keypad5;
    case SDL_SCANCODE_KP_6: return ImGuiKey_Keypad6;
    case SDL_SCANCODE_KP_7: return ImGuiKey_Keypad7;
    case SDL_SCANCODE_KP_8: return ImGuiKey_Keypad8;
    case SDL_SCANCODE_KP_9: return ImGuiKey_Keypad9;
    case SDL_SCANCODE_KP_PERIOD: return ImGuiKey_KeypadDecimal;
    case SDL_SCANCODE_KP_DIVIDE: return ImGuiKey_KeypadDivide;
    case SDL_SCANCODE_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
    case SDL_SCANCODE_KP_MINUS: return ImGuiKey_KeypadSubtract;
    case SDL_SCANCODE_KP_PLUS: return ImGuiKey_KeypadAdd;
    case SDL_SCANCODE_KP_ENTER: return ImGuiKey_KeypadEnter;
    case SDL_SCANCODE_KP_EQUALS: return ImGuiKey_KeypadEqual;
    default: break;
    }
    switch (KeyCode)
    {
    case SDLK_TAB: return ImGuiKey_Tab;
    case SDLK_LEFT: return ImGuiKey_LeftArrow;
    case SDLK_RIGHT: return ImGuiKey_RightArrow;
    case SDLK_UP: return ImGuiKey_UpArrow;
    case SDLK_DOWN: return ImGuiKey_DownArrow;
    case SDLK_PAGEUP: return ImGuiKey_PageUp;
    case SDLK_PAGEDOWN: return ImGuiKey_PageDown;
    case SDLK_HOME: return ImGuiKey_Home;
    case SDLK_END: return ImGuiKey_End;
    case SDLK_INSERT: return ImGuiKey_Insert;
    case SDLK_DELETE: return ImGuiKey_Delete;
    case SDLK_BACKSPACE: return ImGuiKey_Backspace;
    case SDLK_SPACE: return ImGuiKey_Space;
    case SDLK_RETURN: return ImGuiKey_Enter;
    case SDLK_ESCAPE: return ImGuiKey_Escape;
        //case SDLK_APOSTROPHE: return ImGuiKey_Apostrophe;
    case SDLK_COMMA: return ImGuiKey_Comma;
        //case SDLK_MINUS: return ImGuiKey_Minus;
    case SDLK_PERIOD: return ImGuiKey_Period;
        //case SDLK_SLASH: return ImGuiKey_Slash;
    case SDLK_SEMICOLON: return ImGuiKey_Semicolon;
        //case SDLK_EQUALS: return ImGuiKey_Equal;
        //case SDLK_LEFTBRACKET: return ImGuiKey_LeftBracket;
        //case SDLK_BACKSLASH: return ImGuiKey_Backslash;
        //case SDLK_RIGHTBRACKET: return ImGuiKey_RightBracket;
        //case SDLK_GRAVE: return ImGuiKey_GraveAccent;
    case SDLK_CAPSLOCK: return ImGuiKey_CapsLock;
    case SDLK_SCROLLLOCK: return ImGuiKey_ScrollLock;
    case SDLK_NUMLOCKCLEAR: return ImGuiKey_NumLock;
    case SDLK_PRINTSCREEN: return ImGuiKey_PrintScreen;
    case SDLK_PAUSE: return ImGuiKey_Pause;
    case SDLK_LCTRL: return ImGuiKey_LeftCtrl;
    case SDLK_LSHIFT: return ImGuiKey_LeftShift;
    case SDLK_LALT: return ImGuiKey_LeftAlt;
    case SDLK_LGUI: return ImGuiKey_LeftSuper;
    case SDLK_RCTRL: return ImGuiKey_RightCtrl;
    case SDLK_RSHIFT: return ImGuiKey_RightShift;
    case SDLK_RALT: return ImGuiKey_RightAlt;
    case SDLK_RGUI: return ImGuiKey_RightSuper;
    case SDLK_APPLICATION: return ImGuiKey_Menu;
    case SDLK_0: return ImGuiKey_0;
    case SDLK_1: return ImGuiKey_1;
    case SDLK_2: return ImGuiKey_2;
    case SDLK_3: return ImGuiKey_3;
    case SDLK_4: return ImGuiKey_4;
    case SDLK_5: return ImGuiKey_5;
    case SDLK_6: return ImGuiKey_6;
    case SDLK_7: return ImGuiKey_7;
    case SDLK_8: return ImGuiKey_8;
    case SDLK_9: return ImGuiKey_9;
    case SDLK_A: return ImGuiKey_A;
    case SDLK_B: return ImGuiKey_B;
    case SDLK_C: return ImGuiKey_C;
    case SDLK_D: return ImGuiKey_D;
    case SDLK_E: return ImGuiKey_E;
    case SDLK_F: return ImGuiKey_F;
    case SDLK_G: return ImGuiKey_G;
    case SDLK_H: return ImGuiKey_H;
    case SDLK_I: return ImGuiKey_I;
    case SDLK_J: return ImGuiKey_J;
    case SDLK_K: return ImGuiKey_K;
    case SDLK_L: return ImGuiKey_L;
    case SDLK_M: return ImGuiKey_M;
    case SDLK_N: return ImGuiKey_N;
    case SDLK_O: return ImGuiKey_O;
    case SDLK_P: return ImGuiKey_P;
    case SDLK_Q: return ImGuiKey_Q;
    case SDLK_R: return ImGuiKey_R;
    case SDLK_S: return ImGuiKey_S;
    case SDLK_T: return ImGuiKey_T;
    case SDLK_U: return ImGuiKey_U;
    case SDLK_V: return ImGuiKey_V;
    case SDLK_W: return ImGuiKey_W;
    case SDLK_X: return ImGuiKey_X;
    case SDLK_Y: return ImGuiKey_Y;
    case SDLK_Z: return ImGuiKey_Z;
    case SDLK_F1: return ImGuiKey_F1;
    case SDLK_F2: return ImGuiKey_F2;
    case SDLK_F3: return ImGuiKey_F3;
    case SDLK_F4: return ImGuiKey_F4;
    case SDLK_F5: return ImGuiKey_F5;
    case SDLK_F6: return ImGuiKey_F6;
    case SDLK_F7: return ImGuiKey_F7;
    case SDLK_F8: return ImGuiKey_F8;
    case SDLK_F9: return ImGuiKey_F9;
    case SDLK_F10: return ImGuiKey_F10;
    case SDLK_F11: return ImGuiKey_F11;
    case SDLK_F12: return ImGuiKey_F12;
    case SDLK_F13: return ImGuiKey_F13;
    case SDLK_F14: return ImGuiKey_F14;
    case SDLK_F15: return ImGuiKey_F15;
    case SDLK_F16: return ImGuiKey_F16;
    case SDLK_F17: return ImGuiKey_F17;
    case SDLK_F18: return ImGuiKey_F18;
    case SDLK_F19: return ImGuiKey_F19;
    case SDLK_F20: return ImGuiKey_F20;
    case SDLK_F21: return ImGuiKey_F21;
    case SDLK_F22: return ImGuiKey_F22;
    case SDLK_F23: return ImGuiKey_F23;
    case SDLK_F24: return ImGuiKey_F24;
    case SDLK_AC_BACK: return ImGuiKey_AppBack;
    case SDLK_AC_FORWARD: return ImGuiKey_AppForward;
    default: break;
    }

    // Fallback to scancode
    switch (ScanCode)
    {
    case SDL_SCANCODE_GRAVE: return ImGuiKey_GraveAccent;
    case SDL_SCANCODE_MINUS: return ImGuiKey_Minus;
    case SDL_SCANCODE_EQUALS: return ImGuiKey_Equal;
    case SDL_SCANCODE_LEFTBRACKET: return ImGuiKey_LeftBracket;
    case SDL_SCANCODE_RIGHTBRACKET: return ImGuiKey_RightBracket;
    case SDL_SCANCODE_NONUSBACKSLASH: return ImGuiKey_Oem102;
    case SDL_SCANCODE_BACKSLASH: return ImGuiKey_Backslash;
    case SDL_SCANCODE_SEMICOLON: return ImGuiKey_Semicolon;
    case SDL_SCANCODE_APOSTROPHE: return ImGuiKey_Apostrophe;
    case SDL_SCANCODE_COMMA: return ImGuiKey_Comma;
    case SDL_SCANCODE_PERIOD: return ImGuiKey_Period;
    case SDL_SCANCODE_SLASH: return ImGuiKey_Slash;
    default: break;
    }
    return ImGuiKey_None;
}