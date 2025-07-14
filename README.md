Simple console app, that will scan given directory (provided by path) recursively and creates image of the directory tree using "PlantUML".
Resulting image can be saved to the file or viwed immediately.

Uses Python with Pillow and PlantUML under the hood

Features:
* Can also show size of each file and directory
* Can apply a color to every node (directory or file) according to color-scale (from one color to another), color represents size of the object