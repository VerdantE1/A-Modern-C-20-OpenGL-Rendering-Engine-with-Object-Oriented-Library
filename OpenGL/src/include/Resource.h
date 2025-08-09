#pragma once

class Resource
{
public:

	
	Resource() :m_id(0) {}	
	Resource(unsigned int id) : m_id(id) {};

	//Prevent copying
	Resource(const Resource& other) = delete;
	Resource& operator=(const Resource& other) = delete;

	// Could be move but not needed for now
	Resource(Resource&& other) = delete;
	Resource& operator=(Resource&& other) = delete;

	virtual ~Resource() = default;

	unsigned int GetID() const { return m_id; } // Returns the resource ID
	virtual void Bind() const = 0; // Bind the resource to the current context
	virtual void Unbind() const = 0; // Unbind the resource from the current context
	
	
protected:
	unsigned int m_id; 
	
};



