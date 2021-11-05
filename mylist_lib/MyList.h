template <typename T>
struct Node {
	Node(T a) : value(a) {}
	Node(T&& a) : value(std::forward<T>(a)) {}

	T value;
	Node* next = nullptr;
};

template <typename T, typename A = std::allocator<Node<T>>>
class MyList {
public:
	using node_t = Node<T>;
	using allocator_t = typename std::allocator_traits<A>::template rebind_alloc< node_t >;

	MyList() = default;

	void push_back(T&& val)
	{
		Node<T>* new_node = allocator_.allocate(1);
		allocator_.construct(new_node, std::forward<node_t>(val));
		if (head)
		{
			pos->next = new_node;
			pos = pos->next;
		}
		else
		{
			head = new_node;
			pos = head;
		}
		size++;
	}
	const node_t* Head() const
	{
		return head;
	};
	~MyList()
	{
		node_t* head_ = head;
		while (head_ != nullptr)
		{
			node_t* target = head_->next;
			allocator_.destroy(head_);
			allocator_.deallocate(head_, 1);
			head_ = target;
		}

	}
private:
	node_t* head = nullptr;
	node_t* pos;
	std::size_t size = 0;
	allocator_t allocator_{};
};