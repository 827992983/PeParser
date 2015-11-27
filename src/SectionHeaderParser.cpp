#include <stdafx.h>

#include <SectionHeaderParser.h>

const SectionHeaderParser::LayoutType* SectionHeaderParser::layout_{ SectionHeaderLayout::infos.getHolderPtr() };


SectionHeaderParser::SectionHeaderParser(const std::string& filename) : BasicParser(filename)
{
	COFFHeaderParser tmp{ filename };
	if (tmp.isObjectFile())
	{
		init(tmp);
	}
	else
	{
		init(PEHeaderParser{ std::move(tmp) });
	}
}

SectionHeaderParser::SectionHeaderParser(PEHeaderParser& parser) : BasicParser(parser.getFileName())
{
	init(parser);
}

std::streampos SectionHeaderParser::getSectionsBegin() const noexcept
{
	return sectionBegin_;
}

// NOTE : As name is a string, it can not be retrieved by this method. Use "getSectionName" instead !
// Maybe later I'll figure out a better way.
size_type SectionHeaderParser::retrieveFieldValue(size_type index, SectionHeaderField field)
{
	goToSection(index);
	HeaderField tmp = layout_->get(field);
	return reader_.retrieveValue(tmp.offset + reader_.getCurrentPosition(), tmp.size);
}

size_type SectionHeaderParser::getSectionSize(size_type index)
{
	return retrieveFieldValue(index, SectionHeaderField::VirtualSize);
}

// TODO : implement
size_type SectionHeaderParser::getSectionSize(const std::string& name)
{
	return 0;
}

// Check if index is smaller than section number !
std::string SectionHeaderParser::getSectionName(size_type index)
{
	goToSection(index);
	HeaderField nameField = layout_->get(SectionHeaderField::Name);
	std::string tmp;
	std::vector<unsigned char> vectorBuffer = reader_.retrieveRawBuffer(nameField.offset + reader_.getCurrentPosition(), nameField.size);
	for (auto chr : vectorBuffer)
	{
		tmp += static_cast<char>(chr);
	}
	return tmp;
}

size_type SectionHeaderParser::getNumberOfSections() const noexcept
{
	return numberOfSections_;
}

void SectionHeaderParser::goToSection(size_type index)
{
	ensureSectionExists(index);
	HeaderField tmp;
	reader_.goTo(getSectionsBegin());
	while (index != 0)
	{
		tmp = layout_->get(SectionHeaderField::VirtualSize);
		reader_.goTo(reader_.getCurrentPosition() + static_cast<std::streampos>(layout_->getHeaderSize()));
		--index;
	}
	currentSectionIndex_ = index;
}

void SectionHeaderParser::init(COFFHeaderParser& parser)
{
	sectionBegin_ = parser.getHeaderEnd();
	numberOfSections_ = parser.getNumberOfSections();
}

void SectionHeaderParser::init(PEHeaderParser& parser)
{
	sectionBegin_ = parser.getDataDirectoryEnd();
	numberOfSections_ = parser.getNumberOfSections();
}

void SectionHeaderParser::ensureSectionExists(size_type index)
{
	if (index >= numberOfSections_)
	{
		std::stringstream ss;
		ss << index;
		std::string tmp = "Attempting to access a non existing PE section with index ";
		tmp += ss.str();
		ss.str("");
		ss << numberOfSections_;
		tmp += " whereas there's only " + ss.str() + " sections !";
		throw std::out_of_range(tmp);
	}
}