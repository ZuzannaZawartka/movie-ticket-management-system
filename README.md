# Cinema Management System
## Overview
The Cinema Ticket Management System is a cinema system simulation designed to manage all aspects of cinema operations, from scheduling screenings to booking tickets. The application has a friendly interface that allows cinema managers to easily navigate through various functionalities. All data, including movie lists, schedules and reservations with user information, is stored in the database.

## Application Components
- **Main Window**: Manages the user interface and serves as the main window of the application. <br>
- **Manage Movie**: Add, edit, or remove movies from the cinema's listing. <br>
- **Manage Room**: Generate your own cinema room. <br>
- **Book Tickets**: Create and save new bookings in database. <br>
- **Manage Schedule**: Create, modify and remove movie schedules. <br>
- **Manage Bookings**: Oversee all bookings, including editing and removing. <br>
- **Show Movie List**: View the current list of all movies available in the cinema. <br>
- **Show Schedule**: View the current schedule of all movie showings. <br>

## Functionality Description:
Adding and editing movies are restricted by appropriate validators, ensuring data accuracy. Schedules can only be added to existing movies, and if a movie is deleted, all its schedules are automatically removed. This ensures that you can only book tickets for confirmed movie showings. Whenever there are changes in movies or movie schedules, all existing bookings are automatically refreshed.  When a cinema room is changed, all existing bookings are automatically deleted. Canceling a reserved seat makes it available for booking again. Every input in the application is validated appropriately. For example, regular expressions are used to ensure that there is a valid email address in the purchaser details.

## Screenshots
![MainWindow](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/2369d190-3a4a-4a0d-97d3-4b9bf0bf047b)

![ManageMovie](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/897f52a2-bed8-4384-a0b6-98339aff1b9a)

![ManageRoom](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/4c7155ad-3c4e-4450-82f9-c254fd4ed10d)

![ManageSchedule](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/31af138d-4687-42f9-a604-9224b9c9d5b9)

![BookTickets1](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/b47970d1-d88e-4da8-93da-adafea1e3e25)

![BookTickets2](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/68d6c53b-65d9-4b15-ba6d-0564ebd63396)

![ReserveSeats](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/45e0a678-34d4-4173-8208-3d4ae4e1d665)

![PurchaserDetails](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/150afa62-1dd1-4c5a-b71d-dedafbd24fa9)

![ManageBookings](https://github.com/ZuzannaZawartka/movie-ticket-management-system/assets/163564160/7a4ba686-5e91-4692-b371-7a901670d86b)

## Requirements

To build and run this project, you need the following:

- **Visual Studio**: Visual Studio 2022 or later
  - Download Visual Studio from [here](https://visualstudio.microsoft.com/).
    
- **Qt**: Qt 6.7.0 
  - Download Qt from [here](https://www.qt.io/download).
    
- **Qt Visual Studio Tools**: Extension for integrating Qt with Visual Studio
  - Install from Visual Studio's Extensions Manager.
    
- **C++ Toolset**: Ensure that the C++ development tools are installed in Visual Studio
  - Go to Visual Studio Installer and select "Desktop development with C++" workload.

## Running the Application

1. **Download the code**: Copy the Paths Manager application code.
   
   ```bash
     git clone https://github.com/ZuzannaZawartka/movie-ticket-management-system.git
     ```
2. **Open the solution**:
    - Open `MovieTicketManagementSystem.sln` in Visual Studio.

3. **Set up Qt**:
    - Configure Visual Studio to use the installed Qt version by going to `Qt VS Tools > Qt Options` and adding the path to the Qt installation.

4. **Build the solution**:
    - In Visual Studio, go to `Build > Build Solution` or press `Ctrl+Shift+B`.

5. **Run the application**:
    - Set the startup project (if necessary) by right-clicking the project in the Solution Explorer and selecting `Set as StartUp Project`.
    - Press `F5` to run the application.

## Additional Information

- **Configuration**: Make sure to select the correct build configuration (Debug/Release) and platform (x86/x64) as per your requirements.
      
## Graphics Resources

The images used in this project were generated using OpenAI's ChatGPT.
