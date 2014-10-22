#include <ARAM/tools/TagDictionnary.hpp>

namespace aram
{
	Node::Node(int v):m_value(v)
	{
		p_left = NULL;
		p_right = NULL;
	}

	TagDictionnary TagDictionnary::s_instance=TagDictionnary();

	TagDictionnary::TagDictionnary()
	{
		p_root = new Node(-1);
		p_root->p_left = NULL;
		p_root->p_right = NULL;

		read();
	}

	TagDictionnary& TagDictionnary::operator=(const TagDictionnary&)
	{
		return s_instance;
	}

	TagDictionnary::TagDictionnary(const TagDictionnary&)
	{
	}

	TagDictionnary & TagDictionnary::getInstance()
	{
		return s_instance;
	}

	void TagDictionnary::insert(std::bitset<81> bits)
	{
		Node *parentNode = p_root;

		for(int pos=0;pos<81;++pos)
		{
			int v = bits[pos];
			
			switch(v)
			{
			case 0:
				if(parentNode->p_left==NULL) parentNode->p_left = new Node(0);
				parentNode = parentNode->p_left;
				break;
			case 1:
				if(parentNode->p_right==NULL) parentNode->p_right = new Node(1);
				parentNode = parentNode->p_right;
				break;

			default :
				throw ARAMException(__LINE__, __FILE__, "TagDictionnary::insert", "Wrong value");
				break;
			}
		}

		m_sets.push_back(bits);
	}

	bool TagDictionnary::binaryTreeSearch(cv::Mat &bits)
	{
		bool res = true;
		Node *parentNode = p_root;

		for(int row=0;row<9&&res;++row)
		{
			for(int col=0;col<9&&res;++col)
			{
				int v = bits.at<uchar>(row,col);
				switch(v)
				{
				case 0:
					if(parentNode->p_left==NULL) res = false;
						
					parentNode = parentNode->p_left;
					break;

				case 1:
					if(parentNode->p_right==NULL) res = false;

					parentNode = parentNode->p_right;
					break;

				default :
					throw ARAMException(__LINE__, __FILE__, "TagDictionnary::insert", "Wrong value");
					break;
				}
			}
		}

		return res;
	}

	int TagDictionnary::hammingSearch(cv::Mat &bits, int dist)
	{
		std::bitset<81> set;
		for(int i=0;i<9;++i)
		{
			for(int j=0;j<9;++j)
			{
				if(bits.at<uchar>(i,j) == 0) set[i*9+j] = 0;
				else set[i*9+j] = 1;
			}
		}
		
		int min = 81;
		int indMin = m_sets.size();
		for(unsigned int i=0;i<m_sets.size();++i)
		{
			int hammDist = hammingDistance(m_sets[i],set);
			if(hammDist<min)
			{
				min = hammDist;
				indMin = i;
			}
		}

		if(min<dist) return indMin;
		else return -1;
	}

	int TagDictionnary::hammingDistance(std::bitset<81> a, std::bitset<81> b)
	{
		int dist = 0;
		for(int i=0;i<81;++i)
		{
			if(a[i]!=b[i]) dist++;
		}

		return dist;
	}

	void TagDictionnary::read()
	{
		std::vector< std::bitset<81> > tags;
		tags.push_back(std::bitset<81>(std::string("000000000001011000011101110000000010000000110011010000011110110011100010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001111100000100010000100110011001000011010110010000110011001000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011010110000011010011001000011001110010001010010011100000100010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001001110010110010000111000000110110010010110001001100011000110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010101100011010110001100000011110010000101110010001100010101100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010000000010001100011110100010111110000010000010000010011001110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011111010000110100001100100010110110000011100010100100001000010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010100010000001100010101100010101000001111100000001010011001100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010011010011111010001101000001000010010001010011100010011001010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010110100011100110001100110001110100000010110011110000011001100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010111110011000110010001010001111100011000010001111100011000110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011010100010000000001001010001111000011111110001111110010111010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011110100010011110011111010011001100001010000000001100000100110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011100100000110010000010010001100010010100110010000100011110100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001111010011101000010001010010011000010011010011010000011000010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000011110010101000010001000010100010010011110010001100010001100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001101110011111010011010010011001000000111100010111010010000100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010011100010110110000001100010001100010101110000100000000001000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010111110000111000001010100000110110010001000010110010001010010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011110100000110110011101110000101110001010000011110100001101010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000001100010000100010100000000100010011011100010101010000011010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001001110011101010011100110001011010010001000001010010001111100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000001110011110110011011000011011110011100010010111000010111100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010110100001100010010101100010101110000110110011101110000010000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001100110011010000011010010010011000001110110011010100000101000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010111100011010000010000100010100010011111000010100100010111110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010011110010011100001010110001011010010100100010001000001011000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001101000001111000011010110000000000011110010010010000011010100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011100000011000100011110100011100110010101010010100000010100110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011111110001111000010100100000001010010100010010000010000001000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011100110000000100001101000001110100010000010011010010010111110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011011000001111010010000100010011100011011110010111100010011010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001111000011101000010000010010010000010101000000001000011000110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000010101010010110100010010010010010110000000100011000100001100100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000111100011001100010101100010001000010001100000010110010011110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000110100011111110010110000010011010010110000011010100010111000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000111000010010100011101100010110110010001100001101110010110100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011000010000101100011010100010111110011101010000110010011111100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011010110011111010000111000001101110011101010011000110010110000000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011010110001111110010101110010001000001011000001001010010110100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011110000010010110010100110011001000010110000010101010011110110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011000000010111010010101110010101110010001110001001010010011100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011000110011010100010100000011100000011011100001001010000001110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001011100010010100001110110011110000011010110011100010011011010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011101000010110010010010100010101010010101000011101110001100110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000011101000010010000010100010000111000011000100011100000011110110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001110110010001000010111110011111110000101010010001100001010110000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001111000010100000001110100011010110010000000011011010000010010000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000001011110010010000011100100010101100010001110000100010000001100000000000")));
		tags.push_back(std::bitset<81>(std::string("000000000000001110010100000000100100010111110010010100010011110001011110000000000")));

		std::vector< std::bitset<81> >::const_iterator it;
		for(it=tags.begin();it!=tags.end();++it)
		{
			insert(*it);
		}


		return;
	}

};