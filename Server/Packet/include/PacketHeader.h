#pragma once

namespace Packet
{
	struct Header
	{
		struct Buffer
		{
			char* data;

			void Destroy()
			{
				delete[] data;
			}
		};

		int packetID;
		int length;

		static constexpr int Size = 8;

		Header();

		void Init();

		Buffer Serialize();
		void Serialize(void* buffer);
		
		void Deserialize(Buffer buffer);
		void Deserialize(char* data);
	};
}