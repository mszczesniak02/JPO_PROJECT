// Dear ImGui: standalone example application for DirectX 9

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/csv_file.hpp"
#include "ImGui/text_file.hpp"
#include "ImGui/file_factory.cpp"
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <d3d9.h>






namespace fs = std::filesystem;

// -------------------------------------------- IMGUI------------------------------------ 
// Data
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static bool                     g_DeviceLost = false;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



// Main code

std::vector<std::string> list_directory(std::string path){ // THIS FUNC TAKES CARE OF LISTING DIRECTORY
    std::vector<std::string> result;
    for (const auto& entry : fs::directory_iterator(path)) {
        result.push_back(entry.path().string());
    }
    return result;
};

int MAIN_WINDOW_SIZE_X = 500; // SIZE OF MY MAIN WINDOW
int MAIN_WINDOW_SIZE_Y = 550;

File_Factory f;                 // DESIGN PATTERN FACTORY INITIATION
vector<File*> files;
    

int main(int, char**)
{
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

    // --------------------------------------IMGUI--------------------------------
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"FILE ANALYZER", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"FILE ANALYZER", WS_OVERLAPPEDWINDOW, 100, 100, MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.FontGlobalScale = 1.15f;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;

    // my involvement:
    // styling:
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImColor(190,74,47);
    style.WindowRounding = 0.25;


   
    // --------------------------------------PROJECT: --------------------------------
  
    static char abs_path[100] = "";                              //  HOLD USER PATH INPUT  
    bool btn_confirm = false;               //  CONTROLLES THE CONFIRM BUTTON
    // bool show_new_window = false;           //  TESTING
    bool show_window_directory = false;     // ENABLE DIR PICK VIEW
    bool show_window_file_details = false;  // ENABLE FILE LOOK=UP



    string starting_file;                   // CONTROLING THE PATH NAVIGATION FOR CHANGING SCREENS
    string current_file;
    string previous_file;

    // --------------------------------------IMGUI: --------------------------------

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Handle lost D3D9 device
        if (g_DeviceLost)
        {
            HRESULT hr = g_pd3dDevice->TestCooperativeLevel();
            if (hr == D3DERR_DEVICELOST)
            {
                ::Sleep(10);
                continue;
            }
            if (hr == D3DERR_DEVICENOTRESET)
                ResetDevice();
            g_DeviceLost = false;
        }

        // Handle window resize (we don't resize directly in the WM_SIZE handler)
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();



        // ---------------------------PROJECT --------------------------------- 

        ImGui::SetNextWindowPos(ImVec2(0,0));              //SET THE INITIAL POSITION AND SIZE
        ImGui::SetNextWindowSize(ImVec2(500,    550));   // 
        
        
        // WELCOME SCREEN:
        if(ImGui::Begin("MAIN_WINDOW", nullptr, 
            ImGuiWindowFlags_NoCollapse         |       // WINDOW THAT IS NOT RESIZABLE,
            ImGuiWindowFlags_NoResize           |       // AND NOT COLLAPSABLE
            ImGuiWindowFlags_NoDecoration
        )){

        // --------------------------- WELCOME PANEL / FRON PANEL  --------------------------------- 
            
            ImGui::SetCursorPos(ImVec2(0,0));   // LOGO
            io.FontGlobalScale = 2.0f;
            ImGui::Button("FILE ANALYZER FOR WINDOW 10", ImVec2(500,250)); // SOME TEXT / IMAGE OF A DRAGON 
             io.FontGlobalScale = 1.15f;
            ImGui::SetCursorPos(ImVec2(50,275));
            
            ImGui::Button("Type the file/directory below", ImVec2(400,100));    // 
            ImGui::SetCursorPos(ImVec2(80,375));
            ImGui::InputText("##dontShow", abs_path, IM_ARRAYSIZE(abs_path));         // TAKES USER INPUT
            // ImGui::InputText("##absolute_path_input",&absolute_path_input, CHAR_MAX);
            
            ImGui::SetCursorPos(ImVec2(50,400));
            if(ImGui::Button("<-Confirm choise->", ImVec2(400,50))){
                if( abs_path == '\0') {     // IF THE INPUT IS NOTHING, SHOW ERROR
                    ImGui::OpenPopup("Error");
                };
                string abs_path_str(abs_path);
              

                starting_file = fs::path(abs_path_str).string();   // MUST HAVE FOR CHAR& TO STRING CONVERSION
                
                previous_file = starting_file;
                current_file = abs_path_str;            // SET INITIAL SCREEN FOR LATER CHECKING
                
                
            
                
                // LOGIC BEHIND : -> IN A CASE WHERE I GO BACK ENOUGH, I WANT TO GO TO WELCOME SCREEN, NOT FURTHER INTO PARENT PATH
                if ( fs::is_regular_file(current_file) == true){ // IS FILE ?
                    show_window_file_details = true;
                    
                }else if(fs::is_directory(abs_path_str) == true){ // IS DIR ?
                    show_window_directory = true;
                    previous_file = current_file;
                    current_file = abs_path_str;
                }else{
                    ImGui::OpenPopup("Error");  // SEND POPOUT WINDOW
                }
                btn_confirm = false;        //   UN-CLICK THE CONFIRMATION BUTTON
            }
                // POPOUT HANDLER HANDLER
            if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)){
                    ImGui::Text("Invalid input, please select a valid path.");
                    ImGui::Separator();

                    if (ImGui::Button("OK", ImVec2(120, 0))) 
                    {
                        btn_confirm = false; // Close the popup
                        ImGui::CloseCurrentPopup();
                    }
                    ImGui::EndPopup();
                }
            ImGui::SetCursorPos(ImVec2(160 ,460));
            ImGui::Text("M.SZCZESNIAK, id:416855");
     
        }ImGui::End();
   
// ------------------------- MAIN LOGIC ---------------------------------------
        if (show_window_file_details == true) {
            // Set window properties: position and size
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(500, 550), ImGuiCond_Always);
            // PRINTING EACH NEW WINDOW ON TOP OF WELCOME SCREEN

// GET FILE PROPERTIES BY USING FACTORY DESIGN PATTERN
            auto file = f.createFile(current_file); 
                 file->file_properties();
            auto file_stats = file->get_file_properties();
                    file->analyze();
            delete file; // DELETE POSSIBLE MEM LEAKAGE
                
            std::vector<string> file_property_; // LEFT PANEL WHEN SHOWING DATA
            std::vector<string> file_value_;    // RIGHT PANEL
            
                //DETERMINE FILE TYPE
                if(file_stats.extention_ == ".csv"){
                    CSV_File f(current_file);
                    f.analyze(); 
                        std::string col_name;
                        std::string most_word;
                        std::string least_word ;
                        int most, least;

                    for(auto &el : f.s_){
                        col_name = el.column_name_;
                        most = std::get<0>(el.most_popular_);                        
                        most_word = std::get<1>(el.most_popular_);
                        least = std::get<0>(el.most_popular_);                        
                        least_word = std::get<1>(el.most_popular_);
                        file_property_.push_back("Column                :");
                        file_property_.push_back("Most frequent cell    :");
                        file_property_.push_back("Amount                :");
                        file_property_.push_back("Lest Frequent cell    :");
                        file_property_.push_back("Amount                :");
                       
                        file_value_.push_back(col_name);
                        file_value_.push_back(most_word);
                        file_value_.push_back(std::to_string(most));
                        file_value_.push_back(least_word);
                        file_value_.push_back(std::to_string(least));

                        file_property_.push_back("-------------------");
                        file_value_.push_back("-------------------");

                    // PRINT PRETTY FILE DETAILS

                    }
                }else if(file_stats.extention_ == ".txt"){
                    TXT_File f(current_file);
                    f.analyze();
                    auto stats = f.stats_;
                    
                    file_property_.push_back("Letter/Word\t");
                    file_value_.push_back("\tAmount");

                    // LOAD THE BUFFORS (VECTORS) WITH DATA TO SHOW LATER
                    for (int i = 0; i< stats.freq_int.size();i++){
                        file_property_.push_back(stats.freq_str_[i]);
                        file_value_.push_back(std::to_string(stats.freq_int[i]));
                        file_property_.push_back("-------------------");
                        file_value_.push_back("-------------------");
                    }
                }else{ // IF FILE NOT TXT OR CSV 
                    file_property_.push_back("Unfortunatly, This file type is");
                    file_value_.push_back("  ");
                    file_property_.push_back("not supported, use instead.txt or .csv");
                    file_value_.push_back("  ");
                }


            // Create the new window for file details
            if (ImGui::Begin("File Details Window", nullptr, 
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration)) {
            
                ImGui::Text("File Name: %s", current_file.c_str());
                ImGui::Text("Details:");
                    
                ImGui::BeginChild("scrollable_list", ImVec2(0, 400), true);  // Scrollable area

                    // Example of displaying properties (you can populate with real file properties)
                    ImGui::Text("File Path   : %s", file_stats.dir_absolute_.c_str());
                    ImGui::Text("Extention   : %s", file_stats.extention_.c_str());
                    ImGui::Text("Size        : %s B",file_stats.size_.c_str());
                    
                    // PRINT THE BUFFORS
                    for (int i =0 ; i < file_property_.size(); i++){
                        ImGui::Text("%s : %s", file_property_[i].c_str(), file_value_[i].c_str());
                    }

                ImGui::EndChild(); ImGui::Spacing(); // End scrollable list

                // Go back button
                if (ImGui::Button("Go Back", ImVec2(100, 50))) {
                    show_window_file_details = false;  // Close the file details window
                    
                    string temp = current_file;
                    current_file = previous_file;
                    previous_file = current_file ;
                    
                    show_window_directory = true;
                }

                ImGui::End();  // End the file details window
            }
        }

        if (show_window_directory == true) {
            // Set window properties: position and size
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(500, 550), ImGuiCond_Always);
            
         
            // Create the new window for file details
            if (ImGui::Begin("Directory Details", nullptr, 
                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration)) {
                
                ImGui::Text("Directory Name: %s", current_file.c_str());
                ImGui::Text("Content:");
                
                ImGui::BeginChild("scrollable_list", ImVec2(0, 400), true,ImGuiWindowFlags_HorizontalScrollbar);  // Scrollable area
                std::vector<string> dir_content = list_directory(current_file);

                    // HANDLE THE PATH CHANGE
                    for(auto &el: dir_content){
                        if(show_window_file_details == true) break;
                        if (ImGui::Button(el.c_str() )) {
                            // check if is file, is file -> show_window_details_file
                            std::cout<<current_file + el<<"\n";
                            if(fs::is_regular_file(el) == true){
                                previous_file = current_file;
                                current_file = el;
                                show_window_directory = false;
                                show_window_file_details = true;
                                // DYNAMIC CHANGE FROM DIR VIEW TO FILE VIEW
                            }
                            if(fs::is_directory( el) == true ){
                                previous_file = current_file;
                                current_file =  el;
                            }
                        }
                    }
                ImGui::EndChild(); ImGui::Spacing(); // End scrollable list                
                // Go back button
                if (ImGui::Button("Go Back", ImVec2(100, 50))) {

                // IF THE "BACK" BUTTON REACHES THE BEGINING PATH, GO TO WELCOME SCREEN
                    previous_file = current_file ;
                    fs::path path(current_file);
                    
                    current_file = path.parent_path().string();
                    
                    if(current_file == starting_file) {
                        show_window_directory = false;
                    }else show_window_directory = true;  // Close the file details window           
                }                    
                ImGui::End();  // End the file details window
            }   
        }           

// ---------------------------imgui--------------------------------
        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x*clear_color.w*255.0f), (int)(clear_color.y*clear_color.w*255.0f), (int)(clear_color.z*clear_color.w*255.0f), (int)(clear_color.w*255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);
        if (result == D3DERR_DEVICELOST)
            g_DeviceLost = true;
    }

    // Cleanup
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);



// ---------------------------PROJECT--------------------------------
// CLEAN THE MEMORU 
    for (File*& f : files){
        delete f;
    }

    return 0;
    
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
