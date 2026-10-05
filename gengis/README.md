# Geometry Editor

A graphical geometry editor using the GTK library.

## Features

### 1. Panel Creation Mode
- Click to add vertices to the panel
- To close a panel: click on the last point
- Panels are drawn in **blue**

### 2. Cable Creation Mode
- Click on two points to create a cable
- You can click on existing points or create new ones
- Cables are drawn in **green**

### 3. Link Creation Mode
- Click near two **existing** points to create a link
- Links are drawn in **red dotted lines**
- Useful for connecting vertices of different panels or endpoints of cables

## Usage

### Compile
```bash
make
```

### Run
```bash
./gengis
```
ou
```bash
make run
```

### Cleanup
```bash
make clean
```

## Interface

### "File" Menu
- **Save**: Save in dat and don files. dat file is compatible with ./gengis when don file is compatible with the remaining tools of FEMNET
- **Load file**: Load dat file
- **Quit**: Closes the application

### "Actions" Menu
- **Create Panels**: Activates panel creation mode
- **Create Cables**: Activates cable creation mode
- **Create Links**: Activates link creation mode
- **Modify UV**: Change the mesh coordinates of panels points
- **View plane...**: choose the view axis (along X, Y or Z)
- **Clear All**: Clears all objects from the drawing area

### "Zoom" Menu
- **Set Zoom...**: Choose zoom factor (1.0 for 100%)
- **Set Zoom pixel/m**: Choose the ration between pixels (used in Gengis) and m (used in don file)

### "Alignment" Menu
- **Alignment mode**: Select points, cables, and/or panels
- **Modify X**: Change the X coordinates of selected points
- **Modify Y**: Change the Y coordinates of selected points
- **Modify Z**: Change the Z coordinates of selected points
- **Modify Type**: Change the type of selected points, cables, and or panels

### Area Drawing
- **Points**: Displayed in black with a small square
- **Panels**: Blue lines connecting vertices
- **Cables**: Green lines between two points
- **Links**: Red dotted lines between two points

## Code Structure

- `gtk3_main.c`: Main program and interface initialization
- `main.h`: Data structure definitions
- `callbacks.c`: Callback implementation and program logic
- `callbacks.h`: Callback function prototypes
- `gtk3_drawing.c`: Drawing implementation
- `gtk3_drawing.h`: Drawing function prototypes
- `Makefile`: Compilation configuration

## Limits

- Maximum 1000 points
- Maximum 100 panels
- Maximum 100 cables
- Maximum 200 links
- Maximum 50 vertices per panel

## Dependencies

- GTK (graphics library)
- X11, Xaw, Xmu, Xt
- Mathematical library (libm)

## Author

Created with Claude Code
