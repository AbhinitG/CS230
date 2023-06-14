#include <data.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int convertCharToNumber(char ch) {
  if (ch >= '0' && ch <= '9') {
    return ch - '0';
  } else if (ch >= 'A' && ch <= 'F') {
    return ch - 'A' + 10;
  } else {
    return -1;
  }
}

char convertNumberToChar(int n) {
  if (n >= 0 && n <= 9) {
    return n + '0';
  } else if (n >= 10 && n <= 15) {
    return n - 10 + 'A';
  } else {
    return 0;
  }
}

Data convert_to_base_n(Data src, unsigned char n) {
  Data new_data;
  new_data.data = NULL;
  if (n >= 2 && n <= 16) {
    // first convert the n of each data to base 10.
    int base_ten_val = convert_to_base_ten(src);

    new_data.base = n;
    new_data.sign = src.sign;
    new_data.number_bits = src.number_bits;

    DataNode* newHead = NULL;
    DataNode* temp = (DataNode*)malloc(sizeof(DataNode));
    int dividend = base_ten_val / n;
    int remainder = base_ten_val % n;
    temp->number = convertNumberToChar(remainder);
    temp->next = NULL;
    new_data.len = 1;
    while (dividend > 0) {
      remainder = dividend % n;
      dividend /= n;
      newHead = (DataNode*)malloc(sizeof(DataNode));
      newHead->number = convertNumberToChar(remainder);
      newHead->next = temp;
      temp = newHead;
      newHead = NULL;
      new_data.len++;
    }
    new_data.data = temp;
  }
  return new_data;
}

int convert_to_int(Data src) { 
  if (src.sign == 0) {
    return convert_to_base_ten(src);
  }
  else if (src.sign == 1) {
    Data new_data = convert_to_base_n(src, 2);

    int base_ten_val = convert_to_base_ten(new_data);
    if (new_data.number_bits == new_data.len) {
      int val_most_sig_bit = pow(new_data.base, new_data.number_bits - 1) * convertCharToNumber(new_data.data->number);
      base_ten_val -= val_most_sig_bit;
      return base_ten_val - val_most_sig_bit;
    }
    return base_ten_val;    
  }
  else {
    return 0;
  }
}

Data left_shift(Data src, int n) {
  Data new_data = convert_to_base_n(src, 2);

  if (n >= new_data.number_bits) {
    while (new_data.len != 0) {
      remove_head(&new_data.data);
      new_data.len--;
    }
    add_to_head(&new_data.data, '0');
    new_data.len++;
    return new_data;
  }

  for (int i = 0; i < n; i++) {
    if (new_data.len + 1 > new_data.number_bits) {
      remove_head(&new_data.data);
      new_data.len--;
    }
    add_to_tail(&new_data.data, convertNumberToChar(0));
    new_data.len++;
  }

  while (new_data.len > new_data.number_bits || convertCharToNumber(new_data.data->number) == 0) {
    if (new_data.len == 1) {
      break;
    }
    remove_head(&new_data.data);
    new_data.len--;
  }

  return new_data;
}

Data right_shift(Data src, int n) {   
  Data new_data = convert_to_base_n(src, 2);

  if (new_data.number_bits == new_data.len && n > new_data.len) {
    new_data.data = NULL;

    return new_data;
  }
  
  if (new_data.sign == 1) {
    if (new_data.number_bits == new_data.len && convertCharToNumber(new_data.data->number) == 1) {
      for (int i = 0; i < n; i++) {
        add_to_head(&new_data.data, '1');
        remove_tail(&new_data.data);
      }
    }
    else {
      for (int j = 0; j < n; j++) {
        remove_tail(&new_data.data);
        new_data.len--;
      }
    }

    while (new_data.len > new_data.number_bits) {
      remove_tail(&new_data.data);
      new_data.len--;
    }

    while(convertCharToNumber(new_data.data->number) == 0) {
      remove_head(&new_data.data); 
      new_data.len--;
    }
  }
  else {
    for (int x = 0; x < n; x++) {
      remove_tail(&new_data.data);
      new_data.len--; 
    }
  }
  return new_data;
}

int convert_to_base_ten(Data src) {
    int base_ten_val = 0;
    int power = src.len - 1;
    DataNode* pNode = src.data;
    while(pNode) {
      base_ten_val += convertCharToNumber(pNode->number) * pow(src.base, power);
      power--;
      pNode = pNode->next;
    }
  return base_ten_val;
}

Status remove_head(DataNode** data) {
  DataNode* pNode = *data;

  if (pNode == NULL) {
    return FAILURE;
  }
  else {
    DataNode* temp = pNode;
    pNode = pNode->next;
    free(temp);
    *data = pNode;
  }
  return SUCCESS;
}

Status add_to_tail(DataNode** data, unsigned char ch) {
  DataNode* new = (DataNode*)malloc(sizeof(DataNode));
  if (new) {  
    new->number = ch;
    new->next = NULL;
    DataNode* tail = *data;

    if (tail == NULL) {
      *data = new;
    }
    else {
      while (tail->next != NULL) {
        tail = tail->next;
      }
      tail->next = new;
    }
    return SUCCESS;
  }
  return FAILURE;
}

Status add_to_head(DataNode** data, unsigned char ch) {
  DataNode* new = (DataNode*)malloc(sizeof(DataNode));
  if (new) {
    new->number = ch;
    new->next = *data;
    *data = new;
    return SUCCESS;
  }
  return FAILURE;
}

Status remove_tail(DataNode** data) {
  DataNode* prev = NULL;
  DataNode* curr = *data;
  if (!curr) {
    return FAILURE;
  }
  
  if (curr->next == NULL) {
    free(curr);
    *data = NULL;
    return SUCCESS;
  }

  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }
  prev->next = NULL;
  free(curr);
  return SUCCESS;
}