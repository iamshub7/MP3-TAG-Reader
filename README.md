MP3 Tag Reader & Editor (C Programming)
📌 Description

This project is a command-line utility implemented in C for reading and modifying ID3v2.3 metadata in MP3 audio files. It supports frames such as TIT2 (Title), TPE1 (Artist), TALB (Album), TYER (Year), TCON (Genre), and COMM (Comments), allowing users to view or update them without affecting the audio content.

In view mode, the program parses the MP3 file’s ID3 header and displays the tag values in a clean format. In edit mode, it creates a modified copy of the original file with updated tags while preserving all other data. The update process recalculates frame sizes, writes encoding bytes, and ensures proper binary alignment, keeping the MP3 playable.

⚙️ Features

View and edit ID3v2.3 tags

Supports common frames: Title, Artist, Album, Year, Genre, Comments

Safe editing without altering audio data

Recalculates frame sizes and maintains binary alignment

Modular structure with view.c, edit.c, and help.c

Shared header mp3.h for function prototypes and library includes

🛠 Technologies Used

Language: C
Concepts:

File handling

Bit-level data parsing

Structured and modular programming

Binary data manipulation
Platform: Linux
Compiler: GCC

📂 Project Structure

MP3-Tag-Editor/
 ├── view.c       # Display tag data
 ├── edit.c       # Modify tag values
 ├── help.c       # Print usage instructions
 ├── mp3.h        # Shared header with prototypes
 ├── example.mp3  # Sample MP3 file
 └── README.md    # Project documentation


▶️ Usage

🔹 View Tags

./mp3tool -v example.mp3


🔹 Edit Tags

./mp3tool -e example.mp3 -t "New Title" -a "New Artist"


🔹 Help

./mp3tool --help


📚 Learning Outcomes

Understanding MP3 metadata structure and ID3v2.3 format

Practical binary file handling

Bit-level data parsing and modification

Modular C programming

Ensuring data integrity while updating metadata

🚧 Limitations

Supports only ID3v2.3 tags

No audio editing; only metadata modification

Works on standard MP3 files (may not support corrupted or unusual formats)

👨‍💻 Author

Shubham Shinde

📜 License

Open-source, intended for educational purposes