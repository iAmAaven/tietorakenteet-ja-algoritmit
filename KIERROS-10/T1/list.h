#pragma once

#include <iostream>

const int max_list = 10;

enum Error_code
{
    success,
    fail,
    range_error,
    overflow,
    underflow
};

template <class List_entry>
class List
{
public:
    //  methods of the List ADT
    List();
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void (*visit)(List_entry &));
    Error_code retrieve(int position, List_entry &x) const;
    Error_code replace(int position, const List_entry &x);
    Error_code remove(int position, List_entry &x);
    Error_code insert(int position, const List_entry &x);

protected:
    //  data members for a contiguous list implementation
    int count;
    List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List()
{
    count = 0;
}

template <class List_entry>
int List<List_entry>::size() const
{
    return count;
}

template <class List_entry>
bool List<List_entry>::full() const
{
    return count >= max_list;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
    return count == 0;
}

template <class List_entry>
void List<List_entry>::clear()
{
    count = 0;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
    for (int i = 0; i < count; i++)
    {
        (*visit)(entry[i]);
    }
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
{
    if (position < 0 || position >= count)
    {
        return range_error;
    }

    x = entry[position];
    return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
    if (position < 0 || position >= count)
    {
        return range_error;
    }

    entry[position] = x;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
    if (position < 0 || position >= count)
    {
        return range_error;
    }

    x = entry[position];
    for (int i = position; i < count - 1; i++)
    {
        entry[i] = entry[i + 1];
    }

    count--;
    return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
{
    if (full())
    {
        return overflow;
    }

    if (position < 0 || position > count)
    {
        return range_error;
    }

    for (int i = count - 1; i >= position; i--)
    {
        entry[i + 1] = entry[i];
    }

    entry[position] = x;
    count++;
    return success;
}

template <class List_entry>
const char *error_code_name(Error_code code)
{
    switch (code)
    {
    case success:
        return "success";
    case fail:
        return "fail";
    case range_error:
        return "range_error";
    case overflow:
        return "overflow";
    case underflow:
        return "underflow";
    default:
        return "unknown_error";
    }
}

template <class List_entry>
void report_error(const char *function_name, Error_code code)
{
    if (code != success)
    {
        std::cerr << function_name << " failed: " << error_code_name<List_entry>(code) << '\n';
    }
}

template <class List_entry>
Error_code insert_first(const List_entry &x, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If a_list is not full, x is inserted at position 0.
      Else: The function returns overflow.
*/
{
    Error_code result = a_list.insert(0, x);
    report_error<List_entry>("insert_first", result);
    return result;
}

template <class List_entry>
Error_code remove_first(List_entry &x, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If a_list is not empty, its first entry is removed and copied to x.
      Else: The function returns underflow.
*/
{
    if (a_list.empty())
    {
        report_error<List_entry>("remove_first", underflow);
        return underflow;
    }

    Error_code result = a_list.remove(0, x);
    report_error<List_entry>("remove_first", result);
    return result;
}

template <class List_entry>
Error_code insert_last(const List_entry &x, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If a_list is not full, x is inserted as the last entry.
      Else: The function returns overflow.
*/
{
    Error_code result = a_list.insert(a_list.size(), x);
    report_error<List_entry>("insert_last", result);
    return result;
}

template <class List_entry>
Error_code remove_last(List_entry &x, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If a_list is not empty, its last entry is removed and copied to x.
      Else: The function returns underflow.
*/
{
    if (a_list.empty())
    {
        report_error<List_entry>("remove_last", underflow);
        return underflow;
    }

    Error_code result = a_list.remove(a_list.size() - 1, x);
    report_error<List_entry>("remove_last", result);
    return result;
}

template <class List_entry>
Error_code median_list(List_entry &x, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If a_list is not empty, x is assigned the middle entry.
      For even size, the left-central entry is used.
      Else: The function returns underflow.
*/
{
    if (a_list.empty())
    {
        report_error<List_entry>("median_list", underflow);
        return underflow;
    }

    int position = (a_list.size() - 1) / 2;
    Error_code result = a_list.retrieve(position, x);
    report_error<List_entry>("median_list", result);
    return result;
}

template <class List_entry>
Error_code interchange(int pos1, int pos2, List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: If pos1 and pos2 are valid list positions, entries at those positions
      are interchanged.
      Else: The function returns range_error.
*/
{
    int n = a_list.size();
    if (pos1 < 0 || pos1 >= n || pos2 < 0 || pos2 >= n)
    {
        report_error<List_entry>("interchange", range_error);
        return range_error;
    }

    if (pos1 == pos2)
    {
        return success;
    }

    List_entry first_value;
    List_entry second_value;

    Error_code result = a_list.retrieve(pos1, first_value);
    if (result != success)
    {
        report_error<List_entry>("interchange", result);
        return result;
    }

    result = a_list.retrieve(pos2, second_value);
    if (result != success)
    {
        report_error<List_entry>("interchange", result);
        return result;
    }

    result = a_list.replace(pos1, second_value);
    if (result != success)
    {
        report_error<List_entry>("interchange", result);
        return result;
    }

    result = a_list.replace(pos2, first_value);
    report_error<List_entry>("interchange", result);
    return result;
}

template <class List_entry>
void reverse_traverse_list(List<List_entry> &a_list, void (*visit)(List_entry &))
/*
Pre:  a_list exists; visit points to a valid function.
Post: visit is applied to entries of a_list from last to first.
      If retrieval fails unexpectedly, an error is reported and traversal stops.
*/
{
    List_entry x;
    for (int position = a_list.size() - 1; position >= 0; --position)
    {
        Error_code result = a_list.retrieve(position, x);
        if (result != success)
        {
            report_error<List_entry>("reverse_traverse_list", result);
            return;
        }
        visit(x);
    }
}

template <class List_entry>
Error_code copy(List<List_entry> &dest, List<List_entry> &source)
/*
Pre:  dest and source exist.
Post: If dest has enough capacity, dest becomes an exact copy of source.
      Source is unchanged.
      Else: The function returns overflow and dest is cleared.
*/
{
    dest.clear();
    List_entry x;

    for (int i = 0; i < source.size(); ++i)
    {
        Error_code result = source.retrieve(i, x);
        if (result != success)
        {
            report_error<List_entry>("copy", result);
            dest.clear();
            return result;
        }

        result = dest.insert(dest.size(), x);
        if (result != success)
        {
            report_error<List_entry>("copy", result);
            dest.clear();
            return result;
        }
    }

    return success;
}

template <class List_entry>
Error_code join(List<List_entry> &list1, List<List_entry> &list2)
/*
Pre:  list1 and list2 exist.
Post: If list2 has enough remaining capacity, all entries of list1 are appended
      to the end of list2. Existing entries of list2 remain at the beginning.
      list1 is unchanged.
      Else: The function returns overflow and list2 remains unchanged.
*/
{
    List<List_entry> original_list2;
    Error_code result = copy(original_list2, list2);
    if (result != success)
    {
        report_error<List_entry>("join", result);
        return result;
    }

    for (int i = 0; i < list1.size(); ++i)
    {
        List_entry x;
        result = list1.retrieve(i, x);
        if (result != success)
        {
            report_error<List_entry>("join", result);
            copy(list2, original_list2);
            return result;
        }

        result = list2.insert(list2.size(), x);
        if (result != success)
        {
            report_error<List_entry>("join", result);
            copy(list2, original_list2);
            return result;
        }
    }

    return success;
}

template <class List_entry>
void reverse(List<List_entry> &a_list)
/*
Pre:  a_list exists.
Post: Entries of a_list are reversed in order.
      If an internal operation fails unexpectedly, an error is reported and
      partial changes may exist.
*/
{
    int left = 0;
    int right = a_list.size() - 1;

    while (left < right)
    {
        Error_code result = interchange(left, right, a_list);
        if (result != success)
        {
            report_error<List_entry>("reverse", result);
            return;
        }
        ++left;
        --right;
    }
}

template <class List_entry>
Error_code split(List<List_entry> &source, List<List_entry> &oddlist, List<List_entry> &evenlist)
/*
Pre:  source, oddlist, and evenlist exist.
Post: oddlist receives entries from odd-numbered positions of source
      (1st, 3rd, 5th, ...), and evenlist receives entries from even-numbered
      positions (2nd, 4th, 6th, ...). source is unchanged.
      On failure, oddlist and evenlist are restored to their original contents.
*/
{
    List<List_entry> original_odd;
    List<List_entry> original_even;

    Error_code result = copy(original_odd, oddlist);
    if (result != success)
    {
        report_error<List_entry>("split", result);
        return result;
    }

    result = copy(original_even, evenlist);
    if (result != success)
    {
        report_error<List_entry>("split", result);
        return result;
    }

    oddlist.clear();
    evenlist.clear();

    for (int i = 0; i < source.size(); ++i)
    {
        List_entry x;
        result = source.retrieve(i, x);
        if (result != success)
        {
            report_error<List_entry>("split", result);
            copy(oddlist, original_odd);
            copy(evenlist, original_even);
            return result;
        }

        if (i % 2 == 0)
        {
            result = oddlist.insert(oddlist.size(), x);
        }
        else
        {
            result = evenlist.insert(evenlist.size(), x);
        }

        if (result != success)
        {
            report_error<List_entry>("split", result);
            copy(oddlist, original_odd);
            copy(evenlist, original_even);
            return result;
        }
    }

    return success;
}