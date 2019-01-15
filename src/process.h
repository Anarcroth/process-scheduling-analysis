 #ifndef __PROCESS_H_INCLUDED__
#define __PROCESS_H_INCLUDED__

enum class priority : unsigned short;

class process
{
public:
    process();
    process(priority pr);
    process(priority pr, unsigned int ttl);

    priority get_pr() const;
    std::string get_id() const;
    unsigned int get_ttl() const;

private:
    priority set_pr();
    std::string set_id();
    unsigned int set_ttl();

    priority pr;
    std::string id;
    unsigned int ttl;
};

#endif
