# Directory scanner

---

## 💡 Description

Simple console app for Linux, that will scan given directory (provided by path) recursively and creates image of the directory tree using "PlantUML".
Resulting image is saved to the file, provided by output path, or created automatically.

## 🚀 Getting started

To get started, just clone the repo (or just copy /sh/install and /sh/main files) and run "install" script (you probably need to change permissions), it will pull the docker image and you should be good to go.

### 🧰 Prerequisites
* **Docker engine** this program runs inside of docker image, so it won't have to install dependency on your local machine, instructions to install docker can be found here:
    * [Download Docker Desktop](https://www.docker.com/products/docker-desktop)

* **Path to directory** Obviously, the program need directory to scan

### 🔨 Instalation
1. **Clone repo** First you need to clone this repo and navigate to the "/sh" derectory:
    ```bash
    git clone 
    cd sh
    ```
2. **Change permissions and install** Run instalation script, it will pull docker image:
    ```bash
    sudo chmod +x install main
    ./install
    ```

3. **Run the program** That's pretty much it, just run the 'main' script, providing path to the directory and options
    ```bash
    ./main /path/to/directory
    ./install
    ```
4. **(Optional) Create a symlink** For convenience you can create a symlink in your /usr/local/bin directory for easy access to the 'main' script from the terminal
    ```bash
    sudo ln -s ./main /usr/local/bin/dir_scanner_or_whatever
    ```

You can also build the docker image youself, in that case don't bother running 'install' script, build the image and name it "dir_scanner_img:latest", then you should be able to run the 'main' script
```bash
docker build -t dir_scanner_img:latest -f ./Dockerfile .
```


## ▶️ Usage
First provided argument must be a path to the directory you want to scan, absolute and relative paths both work. Next you can specify options, like the type of diagram, do you want the schema to include sizes, which size units should be used, do you want to create color scale or not. Most importantly, you can specify output path, so created diagram will be saved in the file by provided path, it must be an image file (png, jpeg, jpg or svg). The following message will pop up if you mess up the command, it explains every argument:

```bash
Usage: main [PATH] [OPTION]...
Directory scanner. Recursively scans directory, provided by path as the first argument and create image schema representation of that directory.

  -t, --type [b|t|box|tree]     Schema type, can be t (tree) or b (box)
  -b                            Output directory and files sizes in bytes
  -k                            Output directory and files sizes in kilobytes
  -m                            Output directory and files sizes in megabytes
  -g                            Output directory and files sizes in gigabytes
  -o [/path/to/file.png]        Specify output file path (where image schema will be saved), currently only following file formats supported: png, jpeg, jpg, svg
  --color [#xxxxxx-#xxxxxx]     Color range, will be applied to files and directories on the image to mark them with color within range according to size
  --help                        Show this message
```

## PS
If you want to report a bug 🐛 please submit a Github issue with description. If you can improve the sourc code, please submit a pull request, I will be more than happy to get some guidelines and improve the app and my skills😃.

## About author
Hi, my name is Max, I'm a programmer from Russia, I enjoy spending time coding and creating programs like this one. This is my first time creating something that actually can be used in real life and provide actual convenience for the user. I know, the code is still a little bit messy, but I was trying my best, if you can improve it, be my guest and submit a pull request.
Anyway, please enjoy my app. 😇