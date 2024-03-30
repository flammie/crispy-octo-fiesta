use std::fmt::Display;

struct ListItem<T> {
    data: T,
    next: Link<T>
}

pub struct List<T> {
    head: Link<T>
}

type Link<T> =  Option<Box<ListItem<T>>>;

impl<T> List<T> {
    pub fn new() -> Self {
        List { head: None }
    }
    pub fn push(&mut self, value: T) {
        let old_head = self.head.take();
        let new_head = Some(Box::new(ListItem {data: value, next: old_head} ));
        self.head = new_head;
    }
    pub fn pop(&mut self) -> Option<T> {
        self.head.take().map(|li| {
                self.head = li.next;
                li.data
            })
    }
}

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        let mut p = self.head.take();
        while let Some(mut node) = p {
            p = node.next.take();
        }
    }
}

impl<T: Display> std::fmt::Display for List<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "[")?;
        let mut first = true;
        for x in self.iter() {
            if !first {
                write!(f, ",")?;
            }
            write!(f, "{}", x)?;
            first = false;
        }
        write!(f, "]")
    }
}

// a destructive iterator
pub struct IntoIter<T>(List<T>);

impl<T> List<T> {
    pub fn into_iter(self) -> IntoIter<T> {
        IntoIter(self)
    }
}

impl<T> Iterator for IntoIter<T> {
    type Item = T;
    fn next(&mut self) -> Option<T> {
        self.0.pop()
    }
}

// other iterators
pub struct Iter<'a, T> {
    next: Option<&'a ListItem<T>>,
}

impl<T> List<T> {
    pub fn iter(&self) -> Iter<T> {
        Iter { next: self.head.as_deref() }
    }
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;
    fn next(&mut self) -> Option<Self::Item> {
        self.next.map(|node| {
            self.next = node.next.as_deref();
            &node.data
        })
    }
}

//
pub struct IterMut<'a, T> {
    next: Option<&'a mut ListItem<T>>,
}

impl<T> List<T> {
    pub fn iter_mut(&mut self) -> IterMut<T> {
        IterMut { next: self.head.as_deref_mut() }
    }
}

impl<'a, T> Iterator for IterMut<'a, T> {
    type Item = &'a mut T;
    fn next(&mut self) -> Option<Self::Item> {
        self.next.take().map(|node| {
            self.next = node.next.as_deref_mut();
            &mut node.data
        })
    }
}

