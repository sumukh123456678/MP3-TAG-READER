# MP3 Tag Reader Project

This is my project called **MP3 Tag Reader**, written in C language.  
The main idea is to read and display the metadata information (ID3 tags) present inside an MP3 file — like the song title, artist name, album, year, genre, etc.

---

## What It Does

When we play songs, all the information like title, artist, album, etc., comes from something called **ID3 tags** stored inside the MP3 file.  
This project reads those tags directly using file handling in C and prints them in a readable format on the terminal.

---

## Features

- Reads MP3 file metadata (ID3v1 and ID3v2 tags)
- Displays details like:
  - Title  
  - Artist  
  - Album  
  - Year  
  - Genre  
  - Comment  
- Simple command-line interface
- Works with standard MP3 files

---


---

## How It Works

1. The program opens an MP3 file in binary mode.  
2. It reads the **last 128 bytes** of the file (that’s where the ID3v1 tag is stored).  
3. It checks for the tag header `"TAG"` — if found, it extracts and displays the following:
   - Title (30 bytes)  
   - Artist (30 bytes)  
   - Album (30 bytes)  
   - Year (4 bytes)  
   - Comment (30 bytes)  
   - Genre (1 byte)
4. The data is printed nicely in the terminal.

---

## EXAMPLE OUTPUT 
----------------------------------------
           MP3 TAG READER
----------------------------------------
Title   : Shape of You
Artist  : Ed Sheeran
Album   : Divide
Year    : 2017
Genre   : Pop
----------------------------------------



