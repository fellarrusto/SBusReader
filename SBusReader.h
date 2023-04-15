class SBusReader {
  public:
    SBusReader(int numChannels) : numChannels(numChannels) {
      channels = new uint16_t[numChannels];
    }

    ~SBusReader() {
      delete[] channels;
    }

    void begin() {
      Serial1.begin(100000, SERIAL_8E2);
    }

    void update() {
      readData();
    }

    uint16_t getChannel(int channelIndex) {
      return channels[channelIndex];
    }

    uint16_t* getAllChannels() {
      return channels;
    }

  private:
    const int packetLength = 25;
    int numChannels;
    uint8_t buffer[25];
    uint16_t* channels;

    void readData() {
      static int bufferIndex = 0;

      while (Serial1.available()) {
        uint8_t incomingByte = Serial1.read();

        if (bufferIndex == 0 && incomingByte != 0x0F) {
          continue;
        }

        buffer[bufferIndex] = incomingByte;
        bufferIndex++;

        if (bufferIndex == packetLength) {
          parseData();
          bufferIndex = 0;
        }
      }
    }

    void parseData() {
      for (int i = 0; i < numChannels; i++) {
        int byteOffset = i * 11 / 8;
        int bitOffset = i * 11 % 8;
        channels[i] = buffer[1 + byteOffset] >> bitOffset | buffer[2 + byteOffset] << (8 - bitOffset) | buffer[3 + byteOffset] << (16 - bitOffset);
        channels[i] &= 0x07FF;
      }
    }
};