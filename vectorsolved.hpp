#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include<iostream>
namespace sjtu {
	/**
	* a data container like std::vector
	* store data in a successive memory and support random access.
	*/
	template<typename T>
	class vector {
	
	public:
		/**
		* TODO
		* a type for actions of the elements of a vector, and you should write	��
		*   a class named const_iterator with same interfaces.
		*/
		/**
		* you can see RandomAccessIterator at CppReference for help.
		*/
		class const_iterator;
		class iterator {
		private:
			/**
			* TODO add data members
			*   just add whatever you want.
			*/
			
			
		public:
			T * itr;
			vector *vec;
			/**
			* return a new iterator which pointer n-next elements
			*   even if there are not enough elements, just return the answer.
			* as well as operator-
			*/
			iterator(vector * x = NULL, T * y = NULL) :vec(x), itr(y) {}
			//iterator(const vector *  x, T * y = NULL) :vec(x), itr(y) {}
			//iterator() :vec(NULL), itr(NULL) {}
			iterator(const iterator & x) :vec(x.vec), itr(x.itr) {}
			iterator(const const_iterator & x) :vec(x.vec), itr(x.itr) {}
			iterator operator+(const int &n) const {
				//TODO
				iterator  tmp(*this);
				tmp.itr = itr + n;
				return tmp;
			}
			iterator operator-(const int &n) const {
				//TODO
				iterator  tmp(*this);
				tmp.itr = itr - n;
				return tmp;
			}
			// return the distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const iterator &rhs) const {
				//TODO
				if (vec != rhs.vec) throw invalid_iterator();
				int difference;
				difference = (itr > rhs.itr) ? (itr - rhs.itr) : (rhs.itr - itr);
				return difference;
			}

			iterator& operator=(const iterator &x){
				vec = x.vec, itr = x.itr;
				return *this;
			}

			iterator operator+=(const int &n) {
				//TODO
				itr += n;
				return *this;
			}
			iterator operator-=(const int &n) {
				//TODO
				itr -= n;
				return *this;
			}
			/**
			* TODO iter++
			*/
			iterator operator++(int) {
				iterator tmp(*this);
				itr++;
				return tmp;
			}
			/**
			* TODO ++iter
			*/
			iterator& operator++() {
				itr++;
				return *this;
			}
			/**
			* TODO iter--
			*/
			iterator operator--(int) {
				iterator tmp(*this);
				itr--;
				return tmp;
			}
			/**
			* TODO --iter
			*/
			iterator& operator--() {
				itr--;
				return *this;
			}
			/**
			* TODO *it
			*/
			T & operator*() const {
				return *itr;
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			bool operator==(const iterator &rhs) const {
				return (itr == rhs.itr);
			}
			bool operator==(const const_iterator &rhs) const {
				return (itr == rhs.itr);
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const {
				return (itr != rhs.itr);
			}
			bool operator!=(const const_iterator &rhs) const {
				return (itr != rhs.itr);
			}
		};
		/**
		* TODO
		* has same function as iterator, just for a const object.
		*/
		class const_iterator {
		private:
			/**
			* TODO add data members
			*   just add whatever you want.
			*/
			
			
		public:
			T * itr;
			vector *vec;
			/**
			* return a new iterator which pointer n-next elements
			*   even if there are not enough elements, just return the answer.
			* as well as operator-
			*/
			const_iterator(vector * x = NULL, T * y = NULL) :vec(x), itr(y) {}
			//const_iterator(const vector *  x,T * y=NULL) :vec(x), itr(y) {}
			//const_iterator() :vec(NULL), itr(NULL) {}
			const_iterator(const iterator & x) :vec(x.vec), itr(x.itr) {}
			const_iterator(const const_iterator & x) :vec(x.vec), itr(x.itr) {}
			const_iterator operator+(const int &n) const {
				//TODO
				iterator tmp(vec, itr + n);
				return tmp;
			}
			const_iterator operator-(const int &n) const {
				//TODO
				iterator  tmp(vec, itr - n);
				return tmp;
			}
			const_iterator& operator=(const const_iterator &x){
				vec = x.vec, itr = x.itr;
				return *this;
			}
			// return the distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const iterator &rhs) const {
				//TODO
				if (vec != rhs.vec) throw invalid_iterator();
				int difference;
				difference = (itr > rhs.itr) ? (itr - rhs.itr) : (rhs.itr - itr);
				return difference;
			}
			const_iterator operator+=(const int &n) {
				//TODO
				itr += n;
				return *this;
			}
			const_iterator operator-=(const int &n) {
				//TODO
				itr -= n;
				return *this;
			}
			/**
			* TODO iter++
			*/
			const_iterator operator++(int) {
				iterator tmp(*this);
				itr++;
				return tmp;
			}
			/**
			* TODO ++iter
			*/
			const_iterator& operator++() {
				itr++;
				return *this;
			}
			/**
			* TODO iter--
			*/
			const_iterator operator--(int) {
				iterator tmp(*this);
				itr--;
				return tmp;
			}
			/**
			* TODO --iter
			*/
			const_iterator& operator--() {
				itr--;
				return *this;
			}
			/**
			* TODO *it
			*/
            const T & operator*() const {
				return *itr;
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			bool operator==(const iterator &rhs) const {
				return (itr == rhs.itr);
			}
			bool operator==(const const_iterator &rhs) const {
				return (itr == rhs.itr);
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const {
				return (itr != rhs.itr);
			}
			bool operator!=(const const_iterator &rhs) const {
				return (itr != rhs.itr);
			}
		};
		private:
			T * data;
			int currentLength;
			int maxSize;
			iterator head;
			iterator rear;
			char* room;
            void doubleSpace() {
				int i;
				T * tmp = data;
				char* tmproom = room;
				maxSize *= 2;
			    room = new char[maxSize*(sizeof(T))];  //HERE
			    data = (T *)room;    //HERE
				for (i = 0;i < currentLength;++i) new (data + i)T(tmp[i]);//data+i=new (room+) data[i] (tmp[i]);
				//cout << tmp[0];
				//tmp[0].~T();
				for (i = 0;i < currentLength;++i) 
					tmp[i].~T(); 
				delete[] tmproom;
				head.itr = &data[0];
				rear.itr = &data[currentLength - 1];
			}
		/**
		* TODO Constructs
		* Atleast three: default constructor, copy constructor and a constructor for std::vector
		*/
	public:
		vector() {
			maxSize = 10;
			currentLength = 0;
		    room = new char [maxSize*(sizeof(T))] ;  //HERE
		    data = (T *)room;    //HERE
			iterator tmp1(this, data);    //HERE
			iterator tmp2(this, NULL);  //HERE
			head = tmp1;
			rear=tmp2;
		}
		vector(const vector &other) {
			maxSize = other.maxSize;
			currentLength = other.currentLength;
			 room = new char[maxSize*(sizeof(T))];  //HERE
		     data = (T *)room;    //HERE
			for (int i = 0;i < currentLength;++i) { 
				new (data + i) T(other.data[i]);//data+i = new T data[i](other.data[i]);  //HERE
			}
			iterator tmp1(this, &data[0]);
			iterator tmp2(this, &data[currentLength - 1]);
			head = tmp1;
			rear = tmp2;
		}
		/**
		* TODO Destructor
		*/
		~vector() { 
			for (int i = 0;i < currentLength;++i) {
				T * p = data + i;
				p->~T();
			}
			delete[] room; 
		}
		/**
		* TODO Assignment operator
		*/
		vector &operator=(const vector<T> &other) {
			maxSize = other.maxSize;
			currentLength = other.currentLength;
			for (int i = 0;i <currentLength;++i) data[i] = other.data[i];
			return *this;
		}
		/**
		* assigns specified element with bounds checking
		* throw index_out_of_bound if pos is not in [0, size)
		*/
		T & at(const size_t &pos) {
			if (pos >= currentLength || pos < 0) throw index_out_of_bound();
			/*else {
				T tmp ( data[pos]);
				return tmp;
			}*/
			else return data[pos];
		}
		const T & at(const size_t &pos) const {
			if (pos >= currentLength || pos<0) throw index_out_of_bound();
			else return data[pos];
		}
		/**
		* assigns specified element with bounds checking
		* throw index_out_of_bound if pos is not in [0, size)
		* !!! Pay attentions
		*   In STL this operator does not check the boundary but I want you to do.
		*/
		T & operator[](const size_t &pos) {
			if (pos >= currentLength || pos < 0)  throw index_out_of_bound();  
			else {
				 /*T tmp (data[pos]);
				return tmp;*/
				return data[pos];
			}
		}
		const T & operator[](const size_t &pos) const {
			if (pos >= currentLength || pos<0) throw index_out_of_bound();
			else return data[pos];
		}
		/**
		* access the first element.
		* throw container_is_empty if size == 0
		*/
		const T & front() const {
			if (currentLength == 0) throw container_is_empty();
			else return data[0];
		}
		/**
		* access the last element.
		* throw container_is_empty if size == 0
		*/
		const T & back() const {
			if (currentLength == 0) throw container_is_empty();
			else return data[currentLength - 1];
		}
		/**
		* returns an iterator to the beginning.
		*/
		iterator begin() {
			iterator p = head;
			return p;
		}
		const_iterator cbegin() const {
			const_iterator p = head;
			return p;
		}
		/**
		* returns an iterator to the end.
		*/
		iterator end() {
			iterator p(rear.vec, rear.itr + 1);
			return p;
		}
		const_iterator cend() const {
			const_iterator p(rear.vec, rear.itr + 1);
			return p;
		}
		/**
		* checks whether the container is empty
		*/
		bool empty() const {
			return (currentLength == 0);
		}
		/**
		* returns the number of elements
		*/
		size_t size() const {
			return (currentLength );
		}
		/**
		* returns the number of elements that can be held in currently allocated storage.
		*/
		size_t capacity() const {
			return maxSize;
		}
		/**
		* clears the contents
		*/
		void clear() {
			currentLength = 0;
		}
		/**
		* inserts value before pos
		* returns an iterator pointing to the inserted value.
		*/
		iterator insert(iterator pos, const T &value) {
			int i;
			int index = pos.itr - head.itr;
			if (index > currentLength || index < 0) throw index_out_of_bound();
			new (data + currentLength)T(value);//data + currentLength = new (room) data[currentLength]; //HERE
			for ( i = currentLength;i>index;--i) data[i] = data[i - 1];
			data[index] =value;
			currentLength++;
			if (rear.itr == NULL) rear.itr = head.itr;
			else rear.itr++;
			if (currentLength == maxSize - 1) doubleSpace();
			iterator p(head.vec, head.itr + index);
			return p;
		}
		/**
		* inserts value at index ind.
		* after inserting, this->at(ind) == value is true
		* returns an iterator pointing to the inserted value.
		* throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
		*/
		iterator insert(const int &ind, const T &value) {
			if (ind > currentLength || ind < 0) throw index_out_of_bound();
			new (data + currentLength)T(value);//data + currentLength = new (room) data[currentLength](value);  //HERE
			for (int i = currentLength;i > ind;--i) data[i] = data[i - 1];
			//data+ind= new T data[ind](value);
			currentLength++;
			if (rear.itr == NULL) rear.itr = head.itr;
			else rear.itr++;
			if (currentLength == maxSize-1) doubleSpace();
			iterator p(head.vec, head.itr + ind-1);
			return p;
		}
		/**
		* removes the element at pos.
		* return an iterator pointing to the following element.
		* If the iterator pos refers the last element, the end() iterator is returned.
		*/
		iterator erase(iterator pos) {
			if (pos == rear) {
				currentLength--;
				rear.itr--;
				//pos->~T();
				return end();
			}
			else {
				int index = pos.itr - head.itr;
				for (int i = index;i < currentLength - 1;++i) data[i] = data[i + 1];
				//T * tmp = rear.itr;
				currentLength--;
				rear.itr--;
				//tmp->~T();
				iterator p(pos.vec, pos.itr + 1);
				return p;
			}
		}
		/**
		* removes the element with index ind.
		* return an iterator pointing to the following element.
		* throw index_out_of_bound if ind >= size
		*/
		iterator erase(const size_t &ind) {
			if (ind >= currentLength || ind < 0) throw index_out_of_bound();
			for (int i = ind;i < currentLength - 1;++i) data[i] = data[i + 1];
			T * tmp = &data[currentLength];
			currentLength--;
			rear.itr--;
			//tmp->~T();
            iterator p(head.vec, head.itr + ind);
			return p;
		}
		/**
		* adds an element to the end.
		*/
		void push_back(const T &value) {
			new (data + (currentLength++))T(value);
			if (currentLength == maxSize) doubleSpace();
			//insert(currentLength, value);
		}
		/**
		* remove the last element from the end.
		* throw container_is_empty if size() == 0
		*/
		void pop_back() {
			if (currentLength == 0) throw container_is_empty();
			erase(currentLength - 1);
		}
	};


}

#endif
