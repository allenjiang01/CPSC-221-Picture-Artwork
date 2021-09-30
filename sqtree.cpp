/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  stats s = stats(imIn);
  cout << "asdasdasdsad";
  pair<int,int> p = make_pair(0,0);
  root = buildTree(s, p, imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {



  if (h*w == 0) {
    return NULL;
  }
    Node *node = new Node(s, ul, w, h);

  if (node->var <= tol || (node->width == 1 && node->height == 1)) {
    return node;
  }

 double minVar = DBL_MAX;
 pair<int, int> cut; // offset to ul
double maxVar = 0;
for (int x = 0; x < w ; x++) {
    for (int y = 0; y < h ; y++) {
      pair<int, int> NW = make_pair(ul.first, ul.second);
      pair<int, int> NE = make_pair(ul.first + x, ul.second);
      pair<int, int> SW = make_pair(ul.first, ul.second + y);
      pair<int, int> SE = make_pair(ul.first + x, ul.second + y);
      if (x != 0 || y != 0) {
        double nw = s.getVar(NW, x, y);
        double ne = s.getVar(NE, w - x, y);
        double sw = s.getVar(SW, x, h - y);
        double se = s.getVar(SE, w - x, h - y);
        double maxVar = max(max(nw, ne), max(se, sw));
        if (maxVar <= minVar) {
          minVar = maxVar;
	        cut.first = x;
          cut.second = y;
        }
      }
    }
}
//             if (x != 0 && y != 0) {
//         if (s.getVar(NW, x, y) > maxVar) {
//            maxVar = s.getVar(NW, x, y);
//         }
//         if (s.getVar(NE, w-x, y) > maxVar) {
//           maxVar = s.getVar(SW, x, h-y);
//         }
//         if (s.getVar(SW, x, h-y) > maxVar) {
//            maxVar = s.getVar(SW, x, h-y);
//         }
//         if (s.getVar(NE, w-x, h-y) > maxVar) {
//           maxVar = s.getVar(SE, w-x, h-y);
//         }
//         if (maxVar <= minVar) {
//           minVar = maxVar;
//           cut = make_pair(x, y);
//           }
//       }

//       if (x == 0) {
//         if (s.getVar(NE, w, y) > maxVar) {
//           maxVar = s.getVar(NW, w, y);
//         }
//         if (s.getVar(NE, w, h-y) > maxVar) {
//           maxVar = s.getVar(SW, w, h-y);
//         }
//         if (y!=0) {
//           if (maxVar <= minVar) {
//           minVar = maxVar;
//           cut = make_pair(x, y);
//           }
//         }
//       }

//       if (y == 0) {
//         if (s.getVar(NE, x, h) > maxVar) {
//           maxVar = s.getVar(NW, x, h);
//         }
//         if (s.getVar(NE, w-x, h) > maxVar) {
//           maxVar = s.getVar(NE, w-x, h);
//         }
//         if (x!=0) {
//           if (maxVar <= minVar) {
//           minVar = maxVar;
//           cut = make_pair(x, y);
//           }
//         }
//       }
//     }
// }

    pair<int, int> NW = make_pair(ul.first, ul.second);
    pair<int, int> NE = make_pair(ul.first + cut.first, ul.second);
    pair<int, int> SW = make_pair(ul.first, ul.second + cut.second);
    pair<int, int> SE = make_pair(ul.first + cut.first, ul.second + cut.second);

       if (cut.first != 0 || cut.second != 0) {
     cout << "125";
    cout << "\n";
      node->NW = buildTree(s, NW, cut.first, cut.second, tol);
cout << "187";
    cout << "\n";
      node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
      node->SW = buildTree(s, SW, cut.first, h - cut.second, tol);
      node->SE = buildTree(s, SE, w - cut.first, h - cut.second, tol);
      return node;
   }

    if (cut.first != 0 && cut.second != 0) {
  //    cout << "133";
 //   cout << "\n";
      node->NW = buildTree(s, NW, cut.first, cut.second, tol);
      node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
      node->SW = buildTree(s, SW, cut.first, h - cut.second, tol);
      node->SE = buildTree(s, SE, w - cut.first, h - cut.second, tol);
      return node;
    }
    // no y cut
    if (cut.first == 0) {
  //    cout << "143";
 //   cout << "\n";
      node->NW = buildTree(s, ul, w, cut.second, tol);
   //   cout << "146";
  //  cout << "\n";
      node->NE = NULL;
   //   cout << "147";
  //  cout << "\n";
      node->SW = buildTree(s, SW, w, h - cut.second, tol);
    //  cout << "148";
    //cout << "\n";
      node->SE = NULL;
      //cout << "149";
    // cout << "\n";
    //   cout << "%d", &node;
      return node;
    }
    // no x cut
    if (cut.second == 0) {
    //   cout << "153";
    // cout << "\n";
      node->NW = buildTree(s, NW, cut.first, h, tol);
      node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
      node->SW = NULL;
      node->SE = NULL;
      return node;
    }
         }

  // cout << "57";
  //   cout << "\n";
  //   cout << "60";
  //   cout << "\n";
  // pair<int, int> cut; // offset to ul
  // double minVar = DBL_MAX;
  // double maxVar = 0;
  // cout << "61";
  // cout << "\n";
  // for(int x = 0; x < w; x++) {
  //    cout << "65";
  //   cout << "\n";
  //   for(int y = 0; y < h; y++) {
  //     pair<int, int> NW = make_pair(ul.first, ul.second);
  //     pair<int, int> NE = make_pair(ul.first + x, ul.second);
  //     pair<int, int> SW = make_pair(ul.first, ul.second + y);
  //     pair<int, int> SE = make_pair(ul.first + x, ul.second + y);
      
  //     cout << "73";
  //   cout << "\n";
      // case 2 not inital image
    //   if (x != 0 && y != 0) {
    //     if (s.getVar(NW, x, y) > maxVar) {
    //        maxVar = s.getVar(NW, x, y);
    //     }
    //     if (s.getVar(NE, w-x, y) > maxVar) {
    //       maxVar = s.getVar(SW, x, h-y);
    //     }
    //     if (s.getVar(SW, x, h-y) > maxVar) {
    //        maxVar = s.getVar(SW, x, h-y);
    //     }
    //     if (s.getVar(NE, w-x, h-y) > maxVar) {
    //       maxVar = s.getVar(SE, w-x, h-y);
    //     }
    //     if (maxVar <= minVar) {
    //       minVar = maxVar;
    //       cut = make_pair(x, y);
    //       }
    //   }

    //   if (x == 0) {
    //     if (s.getVar(NE, w, y) > maxVar) {
    //       maxVar = s.getVar(NW, w, y);
    //     }
    //     if (s.getVar(NE, w, h-y) > maxVar) {
    //       maxVar = s.getVar(SW, w, h-y);
    //     }
    //     if (y!=0) {
    //       if (maxVar <= minVar) {
    //       minVar = maxVar;
    //       cut = make_pair(x, y);
    //       }
    //     }
    //   }

    //   if (y == 0) {
    //     if (s.getVar(NE, x, h) > maxVar) {
    //       maxVar = s.getVar(NW, x, h);
    //     }
    //     if (s.getVar(NE, w-x, h) > maxVar) {
    //       maxVar = s.getVar(NE, w-x, h);
    //     }
    //     if (x!=0) {
    //       if (maxVar <= minVar) {
    //       minVar = maxVar;
    //       cut = make_pair(x, y);
    //       }
    //     }
    //   }
    // }

  //   node->NW = buildTree(s, ul, cut.first, cut.second, tol);
  //   node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
  //   node->SW = buildTree(s, SW, cut.first, h - cut.second, tol);
  //   node->SE = buildTree(s, SE, w - cut.first, h - cut.second, tol);
  // return node;
  // }
  //        }
         
//    if (cut.first != 0 || cut.second != 0) {
//      cout << "125";
//     cout << "\n";
//       node->NW = buildTree(s, NW, cut.first, cut.second, tol);
// cout << "187";
//     cout << "\n";
//       node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
//       node->SW = buildTree(s, SW, cut.first, h - cut.second, tol);
//       node->SE = buildTree(s, SE, w - cut.first, h - cut.second, tol);
//       return node;
//    }

//     if (cut.first != 0 && cut.second != 0) {
//   //    cout << "133";
//  //   cout << "\n";
//       node->NW = buildTree(s, NW, cut.first, cut.second, tol);
//       node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
//       node->SW = buildTree(s, SW, cut.first, h - cut.second, tol);
//       node->SE = buildTree(s, SE, w - cut.first, h - cut.second, tol);
//       return node;
//     }
//     // no y cut
//     if (cut.first == 0) {
//   //    cout << "143";
//  //   cout << "\n";
//       node->NW = buildTree(s, ul, w, cut.second, tol);
//    //   cout << "146";
//   //  cout << "\n";
//       node->NE = NULL;
//    //   cout << "147";
//   //  cout << "\n";
//       node->SW = buildTree(s, SW, w, h - cut.second, tol);
//     //  cout << "148";
//     //cout << "\n";
//       node->SE = NULL;
//       //cout << "149";
//     // cout << "\n";
//     //   cout << "%d", &node;
//       return node;
//     }
//     // no x cut
//     if (cut.second == 0) {
//     //   cout << "153";
//     // cout << "\n";
//       node->NW = buildTree(s, NW, cut.first, h, tol);
//       node->NE = buildTree(s, NE, w - cut.first, cut.second, tol);
//       node->SW = NULL;
//       node->SE = NULL;
//       return node;
//     }
//          }
  
         

  
/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG img = PNG(root->width, root->height);
  render(img, root);
  return img;
}

void SQtree::render(PNG &img, Node *node) {       // we're only printing
  if (node == NULL) return;
  if (node->NE == NULL && node->NW == NULL && node->SW == NULL && node->SE == NULL) {
    for (int x = 0; x < node->width; x++) {
      for (int y = 0; y < node->height; y++) {
        RGBAPixel * pixel = img.getPixel(node->upLeft.first + x, node->upLeft.second + y);
        *pixel = node->avg;
      }
    }
  } else {
    if (node->NW != NULL) render(img, node->NW);
    if (node->NE != NULL) render(img, node->NE);
    if (node->SW != NULL) render(img, node->SW);
    if (node->SE != NULL) render(img, node->SE);
  }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  if (root == NULL) {
    return;
  }
  clear(root);
}

void SQtree::clear(Node *node) {
  if (node == NULL) {
    return;
  }

  clear(node->SW);
  clear(node->SE);
  clear(node->NE);
  clear(node->NW);
  delete node;
  node = NULL;
}

void SQtree::copy(const SQtree & other) {
  root = copy_(other.root);
}


SQtree::Node* SQtree::copy_(Node* node) {
  if (node != NULL) {
    
    Node* copy = new Node (node->upLeft, node->width, node->height, node->avg, node->var);

    copy->NW = copy_(node->NW);
    copy->NE = copy_(node->NE);
    copy->SW = copy_(node->SW);
    copy->SE = copy_(node->SE);
    return copy;
    
  }
  return NULL;
}


int SQtree::size() {
    return size(root);
}


int SQtree::size(const Node *node) {
  if (node == NULL) {
    return 0;
  }
  // int size = 1 + size(node->NE) + size(node->NW) + size(node->SE) + size(node->SW);
  return 1 + size(node->NE) + size(node->NW) + size(node->SE) + size(node->SW);
}
