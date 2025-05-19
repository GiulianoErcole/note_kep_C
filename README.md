 📝 note_kep_C

A simple and secure terminal-based note-taking tool written in C. Notes are timestamped, XOR-encrypted, and stored in a text file. You can read, search, and append notes from the command line — lightweight and minimal.

---

 🔐 Features

- ✍️ Add timestamped notes
- 🔒 XOR encryption for basic note obfuscation
- 🔍 Keyword search in notes
- 📖 Read-only mode to view stored notes
- 📂 Custom file support
- ⚠️ Warns if note file exceeds 1MB
- 🌈 Colored terminal output for better UX

---

 🚀 Compile

```bash
gcc note_kep_C.c -o note_keeper
```

---

🧠 Usage

```bash
./note_keeper                    # Add a note to the default file (notes.txt)
./note_keeper yourfile.txt      # Add a note to a specific file
./note_keeper -r                # Read all notes from the default file
./note_keeper yourfile.txt -r   # Read all notes from a specific file
./note_keeper -s keyword        # Search for a keyword in default file
./note_keeper yourfile.txt -s keyword  # Search in specific file
```

---

 ✨ Example

```bash
$ ./note_keeper void2
Write a note: system initialized

📒 Your notes:
[2025-05-19 11:28:24] system initialized

$ cat void2
^Ahjhowjowkczkk`hb`hn^Gz.23)z3)z;z.?).P  ← (Encrypted content)
```

---

 🛡️ Encryption Info

- Uses a basic **XOR cipher** with a fixed key: `0x5A`
- Lightweight and fast, but not secure for sensitive data
- For educational and low-risk logging purposes

---

 📁 Notes Format

Each note is stored with a timestamp in a file like:

```
[YYYY-MM-DD HH:MM:SS] your note text
```

- Default file: `notes.txt`
- You can provide a custom filename

---

 🧪 Compatibility

- ✅ Linux (Ubuntu, Arch, etc.)
- ✅ macOS
- ✅ WSL on Windows

---

 🔧 To-Do / Ideas

- [ ] Use AES for real encryption (via OpenSSL)
- [ ] Multiline input
- [ ] Password-based encryption
- [ ] TUI with `ncurses`
- [ ] Export notes to JSON or CSV

---

 👤 Author

Made with ❤️ by `GiulianoErcole`

---

 📜 License

This project is open source and free to use under the [MIT License](LICENSE).
