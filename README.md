# C-PRESENT GUI

The C++ implementation provides a graphical interface for the PRESENT cipher, leveraging SFML for rendering, and integrates the `c-present` library for encryption and decryption operations.

- **Repo:** [Local GUI Project]  
- **Implementation:** `main.cpp` (integrates GUI, key management, and interactive text blocks)

## GUI Usage

The GUI allows users to interactively input data (HEX only), encrypt or decrypt text blocks, and manage the encryption key.

**Features:**

- **Input Field:** Accepts hexadecimal input. Users can type characters or delete them using backspace.  
- **Drop Input Button:** Converts the current input text into a falling text block displayed on the screen.  
- **Encrypt / Decrypt Buttons:** Encrypts or decrypts selected text blocks using the current PRESENT key.  
- **Change Key Button:** Allows the user to enter a new 128-bit key. While the key is being entered, the key display blinks to indicate that the GUI is in key-changing mode. Press Enter to finalize the key.  
- **Falling Text:** Text blocks appear and animate across the screen. Once a block moves outside the window, it is removed from memory.  
- **Key Display:** Shows the current key in hexadecimal format. If a key change is in progress, the display shows the new key being typed and blinks for visibility.

**User Interaction Example:**

1. Launch the GUI.  
2. Type hexadecimal input in the input field.  
3. Press **Drop Input** to create a falling text block.  
4. Click **<- Encrypt** to encrypt or **<- Decrypt** to decrypt the displayed blocks.  
5. Click **Change Key** to enter a new key; type up to 16 hex characters, then press Enter to apply.

## Library Usage

The GUI relies on the `c-present` library for cryptographic operations. The following functions are utilized:

- `set_key(cp_key_t key)` – Sets the current cipher key.  
- `encrypt_block(unsigned long long block)` – Encrypts a 64-bit block.  
- `decrypt_block(unsigned long long block)` – Decrypts a 64-bit block.

The GUI wraps these functions and provides user-friendly interaction via SFML.

## Dependencies

- **SFML 2.x** – Used for window management, drawing, and text rendering.  
- **c-present library** – Provides the cryptographic primitives for encryption and decryption.

This will build the GUI executable using the provided makefile. Ensure that SFML and the c-present library are correctly installed and linked.